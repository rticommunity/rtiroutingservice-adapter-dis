/*
 * (c) 2022 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software solely in combination with RTI Connext DDS. Licensee
 * may redistribute copies of the Software provided that all such copies are
 * subject to this License. The Software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the Software. RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the Software. For purposes of clarity, nothing in this
 * License prevents Licensee from using alternate versions of DDS, provided
 * that Licensee may not combine or link such alternate versions of DDS with
 * the Software.
 */

/* ========================================================================= */
/* RTI Routing Service DIS Socket Adapter                            */
/* ========================================================================= */
/*                                                                           */
/* Serialization.c                                                           */
/*                                                                           */
/* ========================================================================= */

#if defined(RTI_UNIX) && !defined(RTI_LINUX) && !defined(RTI_IRIX) \
        && !defined(RTI_ENDIAN_LITTLE)
    #define RTI_CDR_SIZEOF_LONG_DOUBLE 16
#endif

#include <ndds/ndds_c.h>
#include <dds_c/dds_c_infrastructure.h>
#include <dds_c/dds_c_dynamicdata.h>
#include <routingservice/routingservice_adapter.h>

#include "NetworkConversions.h"
#include "DisSerializer.h"

#ifdef RTI_WIN32
    /* strtok warnings */
    #pragma warning(disable : 4996)
    /* Windows name for snprintf */
    #define snprintf sprintf_s
#endif

extern RTI_RoutingServiceVerbosity _verbosity;

#define CHECK_TYPECODE_OP(ex, returnIfError)  \
    if (ex != DDS_NO_EXCEPTION_CODE) {        \
        printf("%s: %s %d\n",                 \
               FUNCTION_NAME,                 \
               "Failed typecode check, ex: ", \
               ex);                           \
        returnIfError;                        \
    }

DDS_Boolean DDS_TCKind_is_primitive(DDS_TCKind kind)
{
    switch (kind) {
    case DDS_TK_SHORT:
    case DDS_TK_USHORT:
    case DDS_TK_LONG:
    case DDS_TK_ULONG:
    case DDS_TK_CHAR:
    case DDS_TK_OCTET:
    case DDS_TK_WCHAR:
    case DDS_TK_BOOLEAN:
    case DDS_TK_FLOAT:
    case DDS_TK_DOUBLE:
    case DDS_TK_LONGLONG:
    case DDS_TK_ULONGLONG:
    case DDS_TK_LONGDOUBLE:
    case DDS_TK_ENUM:
        return DDS_BOOLEAN_TRUE;

    default:
        return DDS_BOOLEAN_FALSE;
    }
}

RTIBool isBasicTypeCode(
        const struct DDS_TypeCode *tc,
        DDS_TCKind *kind,
        DDS_TCKind *elementKind,
        DDS_UnsignedLong *length,
        DDS_ExceptionCode_t *ex)
{
    struct DDS_TypeCode *elementTc;

    *length = 0;
    *elementKind = DDS_TK_NULL;
    *kind = DDS_TypeCode_kind(tc, ex);
    if (*ex != DDS_NO_EXCEPTION_CODE) {
        return RTI_FALSE;
    }

    switch (*kind) {
    case DDS_TK_SHORT:
    case DDS_TK_LONG:
    case DDS_TK_USHORT:
    case DDS_TK_ULONG:
    case DDS_TK_FLOAT:
    case DDS_TK_DOUBLE:
    case DDS_TK_BOOLEAN:
    case DDS_TK_CHAR:
    case DDS_TK_OCTET:
    case DDS_TK_LONGLONG:
    case DDS_TK_ULONGLONG:
    case DDS_TK_LONGDOUBLE:
    case DDS_TK_WCHAR:
        return RTI_TRUE;
        break;
    case DDS_TK_ENUM: {
        /*
        const DDS_Char * typeName = DDS_TypeCode_name(tc,ex);
        if (*ex != DDS_NO_EXCEPTION_CODE) {
                return RTI_FALSE;
        }
        printf("\nEnum type name is %s\n", typeName);
        */
        return RTI_TRUE;
    } break;
    case DDS_TK_WSTRING:
    case DDS_TK_STRING:
        *length = DDS_TypeCode_length(tc, ex);
        if (*ex != DDS_NO_EXCEPTION_CODE) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
        break;

    /*
     * case DDS_TK_SEQUENCE:
     *   *length = 0;
     *   *kind = DDS_TypeCode_kind(DDS_TypeCode_content_type(tc,ex),ex);
     */
    case DDS_TK_ALIAS: {
        elementTc = DDS_TypeCode_content_type(tc, ex);

        if (*ex != DDS_NO_EXCEPTION_CODE) {
            return RTI_FALSE;
        }

        return isBasicTypeCode(elementTc, kind, elementKind, length, ex);
    } break;

    case DDS_TK_ARRAY: {
        DDS_UnsignedLong arrayLen;
        RTIBool retCode;
        elementTc = DDS_TypeCode_content_type(tc, ex);

        if (*ex != DDS_NO_EXCEPTION_CODE) {
            return RTI_FALSE;
        }

        arrayLen = DDS_TypeCode_length(tc, ex);
        if (*ex != DDS_NO_EXCEPTION_CODE) {
            return RTI_FALSE;
        }

        *elementKind = DDS_TypeCode_kind(elementTc, ex);

        if (*ex != DDS_NO_EXCEPTION_CODE) {
            return RTI_FALSE;
        }

        if (*elementKind == DDS_TK_ALIAS) {
            elementTc = DDS_TypeCode_content_type(tc, ex);
            retCode = isBasicTypeCode(
                    elementTc,
                    elementKind,
                    elementKind,
                    length,
                    ex);
        }
        *length = arrayLen;
        if (*elementKind == DDS_TK_CHAR || *elementKind == DDS_TK_OCTET) {
            return RTI_TRUE;
        }
    } break;

    /*
     * case DDS_TK_SEQUENCE:
     *      elementTc = DDS_TypeCode_content_type(tc,ex);
     *      return RTI_FALSE;
     */
    default:
        return RTI_FALSE;
    }

    return RTI_FALSE;
}

typedef struct {
    int specialAlignment;  /* bytes (4 or 8) */
    /* unsigned long    seqLen; */
    DDS_TCKind tk;
    const char *pSeqName;
    const char *pSeqLenName;
} SeqList;

SeqList seqList[] = {
    { 0, DDS_TK_USHORT, (char*) "m_IntercomData", (char*) "m_ui16Length" },
    { 0,
      DDS_TK_USHORT,
      (char*) "m_AggTyp",
      (char*) "m_ui16NumSilentAggregates" },
    { 0, DDS_TK_USHORT, (char*) "m_vEA", (char*) "m_ui16NumEnts" },
    { 0, DDS_TK_ULONG, (char*) "m_v8DatumValue", (char*) "m_ui32DatumLength" },
    /* Aggregate_State_PDU.idl */
    { 0, DDS_TK_USHORT, (char*) "m_vAI", (char*) "m_ui16NumAggregates" },
    { 0, DDS_TK_USHORT, (char*) "m_vEI", (char*) "m_ui16NumEntities" },
    { 0,
      DDS_TK_USHORT,
      (char*) "m_vSASL",
      (char*) "m_ui16NumSilentAggregateTypes" },
    { 0,
      DDS_TK_USHORT,
      (char*) "m_vSESL",
      (char*) "m_ui16NumSilentEntityTypes" },
    { 0, DDS_TK_ULONG, (char*) "m_vVD", (char*) "m_ui32NumVrblDatum" },
    /* Areal_Object_State_PDU.idl */
    { 0, DDS_TK_USHORT, (char*) "m_vPoints", (char*) "m_ui16NumPoints" },
    /* Comment_PDU.idl */
    { 0, DDS_TK_ULONG, (char*) "m_vFixedDatum", (char*) "m_ui32NumFixedDatum" },
    { 0,
      DDS_TK_ULONG,
      (char*) "m_vVariableDatum",
      (char*) "m_ui32NumVariableDatum" },
    /* Data_Query_PDU.idl
     * dup    {DDS_TK_ULONG, DDS_TK_ULONG,
     * "m_vFixedDatum","m_ui32NumFixedDatum"}, dup    {0, DDS_TK_ULONG,
     * "m_vVariableDatum","m_ui32NumVariableDatum"}, Detonation_PDU.idl test djs
     * {0, DDS_TK_OCTET, "m_vArticulationParameters", (char *)
     * "m_ui8NumOfArticulationParams"},
     */
    { 0,
      DDS_TK_ULONG,
      (char*) "m_vArticulationParameters",
      (char*) "m_ui8NumOfArticulationParams" },
    /* Directed_Energy_Fire_PDU.idl */
    { 4,
      DDS_TK_USHORT,
      (char*) "m_vDeRec",
      (char*) "m_ui16NumDERecs" },  /* 6-byte structs, pad to 32-bit boundary */
                                    /* after sequence. */
                                    /* EmissionSystem */
    { 0,
      DDS_TK_OCTET,
      (char*) "m_vEmitterBeams",
      (char*) "m_ui8NumberOfBeams" },
    /* EmitterBeam */
    { 0,
      DDS_TK_OCTET,
      (char*) "m_vTrackJamTargets",
      (char*) "m_ui8NumTargetInTrackJamField" },
    /* Entity_Damage_Status_PDU.idl */
    /*    {0, 0, "m_vDeRec","m_ui16NumDERecs"}, */
    /* EntityStatePDU.idl */
    { 0,
      DDS_TK_OCTET,
      "m_vArticulationParameters",
      "m_ui8NumOfArticulationParams" },
    /* EntityStateUpdatePDU.idl */
    /* dup    {0, DDS_TK_OCTET,
    "m_vArticulationParameters","m_ui8NumOfArticulationParams"}, */
    /* Environmental_Process_PDU.idl */
    { 0 /*8*/,
      DDS_TK_USHORT,
      (char*) "m_vEnvRecords",
      (char*) "m_ui16NumEnvRec" },
    /* Gridded_Data_PDU.idl */
    { 0, DDS_TK_OCTET, (char*) "m_vpGridAxisDesc", (char*) "m_ui8NumAxis" },
    { 0, DDS_TK_OCTET, (char*) "m_vGridData", (char*) "m_ui8VecDim" },
    /* Intercom_Control_PDU.idl */
    { 0, DDS_TK_ULONG, (char*) "m_vICP", (char*) "m_ui32IntrParamLen" },
    /* Intercom_Signal_PDU */
    /* m_ui16DataLength is bits!!! */
    { 0, DDS_TK_USHORT, (char*) "m_vData", (char*) "m_ui16DataLength" },
    /* IO_Action_PDU.idl */
    { 4, DDS_TK_USHORT, (char*) "m_vStdVarRecs", (char*) "m_ui16NumStdVarRec" },
    /* Linear_Object_State_PDU.idl */
    { 0, DDS_TK_OCTET, (char*) "m_vSegments", (char*) "m_ui8NumSegment" },
    /*  Record_Query_R_PDU.idl */
    { 0, DDS_TK_ULONG, (char*) "m_vui32RecID", (char*) "m_ui32NumRecs" },
    /* Set_Record_R_PDU.idl */
    { 0, DDS_TK_ULONG, (char*) "m_vRecs", (char*) "m_ui32NumRecSets" },
    /* Signal_PDU.idl */
   /*  m_ui16DataLength is bits!!!
    dup    {0, DDS_TK_USHORT, "m_vData","m_ui16DataLength"},
    Transfer_Control_Request_PDU.idl
       {0, DDS_TK_ULONG, "m_vRecs","m_ui32NumRecSets"}, */
    /* Transmitter_PDU.idl */
    { 0,
      DDS_TK_OCTET,
      (char*) "m_vModulationParams",
      (char*) "m_ui8LengthOfModulationParam" },
    { 0,
      DDS_TK_USHORT,
      (char*) "m_vAntennaPattern",
      (char*) "m_ui16AntennaPatternLength" },
    /* TSPI_PDU.idl */
    { 0, DDS_TK_OCTET, (char*) "m_vSSD", (char*) "m_ui8SSDLen" },
};
RTIBool deserializeFields(
        const struct DDS_TypeCode *tc,
        DDS_DynamicData *sample,  /* Out */
        DDS_DynamicData *parent,  /* Out */
        DDS_Char *stream,         /* In */
        DDS_Long *totalBytesRead, /* Out */
        DDS_Long seqNumber = 0,
        const char *seqName = NULL);

DDS_Long serializeFields(
        const struct DDS_TypeCode *tc,
        DDS_DynamicData *sample, /* In */
        DDS_DynamicData *parent, /* In */
        DDS_Char *stream,        /* Out */
        DDS_UnsignedLong maxBuffLen,
        RTI_RoutingServiceEnvironment *env,
        const char *seqName = NULL);

/**
 * @brief Returns the member value of the DynamicData sample
 * The member can be found by looking up by member name or member Id.
 *
 * @param sample. The DynamicData sample (IN)
 * @param memberKind. The member kind needed to parse the value (IN)
 * @param memberName. The member name to be returned. This param can be NULL to
 * look up by the memberId (IN)
 * @param memberId. The member unique id used for look up the member.
 *                  This param can be  DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED to
 * look up by the memberName (IN)
 * @param pValue. The value of the member if it is found.(OUT)
 *
 * @return True if the member has been found and the value has been parsed.
 * False otherwise.
 */

RTIBool getValue(
        struct DDS_DynamicData *sample, /* In */
        DDS_TCKind memberKind,
        const DDS_Char *memberName,
        DDS_DynamicDataMemberId memberId,
        void *pValue)
{
    const DDS_Char FUNCTION_NAME[] = "getValue";
    DDS_ReturnCode_t retCode;

    if (sample == NULL || pValue == NULL) {
        return RTI_FALSE;
    }
#ifdef ENABLE_DIS_DEBUG_MSGS
    if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
        printf("%s:Getting Value %s ",
               FUNCTION_NAME,
               memberName ? memberName : "");
#endif
    switch (memberKind) {
    case DDS_TK_CHAR: {
        DDS_Char charValue;
        DDS_Char *charPtr = (DDS_Char*) pValue;
        retCode = DDS_DynamicData_get_char(
                sample,
                &charValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
            *charPtr = charValue;
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %d (%x)\n", *charPtr, *charPtr);
#endif
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_OCTET: {
        DDS_Octet octetValue;
        DDS_Octet *octetPtr = (DDS_Octet*) pValue;
        retCode = DDS_DynamicData_get_octet(
                sample,
                &octetValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
            *octetPtr = octetValue;
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %d (%x)\n", *octetPtr, *octetPtr);
#endif
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_BOOLEAN: {
        DDS_Boolean boolValue;
        DDS_Boolean *boolPtr = (DDS_Boolean*) pValue;
        retCode = DDS_DynamicData_get_octet(
                sample,
                &boolValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
            *boolPtr = boolValue;
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %d\n", *boolPtr);
#endif
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_SHORT: {
        DDS_Short shortValue;
        DDS_Short *shortPtr = (DDS_Short*) pValue;
        retCode = DDS_DynamicData_get_short(
                sample,
                &shortValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %d (%x)\n", shortValue, shortValue);
#endif
            *shortPtr = shortValue;
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_USHORT: {
        DDS_UnsignedShort uShortValue;
        DDS_UnsignedShort *uShortPtr = (DDS_UnsignedShort*) pValue;

        retCode = DDS_DynamicData_get_ushort(
                sample,
                &uShortValue,
                memberName,
                memberId);

        if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %d (%x)\n", uShortValue, uShortValue);
#endif
            *uShortPtr = uShortValue;
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_ENUM:
    case DDS_TK_LONG: {
        DDS_Long longValue;
        DDS_Long *longPtr = (DDS_Long*) pValue;
        retCode = DDS_DynamicData_get_long(
                sample,
                &longValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %ld (%8x)\n", longValue, longValue);
#endif
            *longPtr = longValue;
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_ULONG: {
        DDS_UnsignedLong uLongValue;
        DDS_UnsignedLong *uLongPtr = (DDS_UnsignedLong*) pValue;
        retCode = DDS_DynamicData_get_ulong(
                sample,
                &uLongValue,
                memberName,
                memberId);
        if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %ld (%08x)\n", uLongValue, uLongValue);
#endif
            *uLongPtr = uLongValue;
            return RTI_TRUE;
        }
    } break;

    case DDS_TK_LONGLONG:
    /*                    {
                           DDS_LongLong longLongValue;
                           DDS_LongLong *longLongPtr = (DDS_LongLong
                           *)pValue; retCode = DDS_DynamicData_get_longlong(
                               sample, &longLongValue, memberName, memberId);
                           if (retCode == DDS_RETCODE_OK) {
        #ifdef ENABLE_DIS_DEBUG_MSGS
           if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
               printf("value: %lld (%016x)\n", longLongValue, longLongValue);
        #endif
                               *longLongPtr = longLongValue;
                           }
                       }
                       break; */

    case DDS_TK_ULONGLONG:
        /*                {
                           DDS_UnsignedLongLong uLongLongValue;
                           DDS_UnsignedLongLong *uLongLongPtr =
                           (DDS_UnsignedLongLong *)pValue; retCode =
                           DDS_DynamicData_get_ulonglong(
                               sample, &uLongLongValue, memberName,
                               memberId);
                           if (retCode == DDS_RETCODE_OK) {
        #ifdef ENABLE_DIS_DEBUG_MSGS
           if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
               printf("value: %lld\n", uLongLongValue);
        #endif
                               *uLongLongPtr = uLongLongValue;
                           }
                       }
                       break; */

    case DDS_TK_FLOAT:
    case DDS_TK_DOUBLE:
    case DDS_TK_STRING:
    case DDS_TK_WCHAR:
    case DDS_TK_LONGDOUBLE:
    case DDS_TK_ARRAY:
    case DDS_TK_SEQUENCE:
    case DDS_TK_WSTRING:
    default:
        goto error;
        break;
    }

error:
    printf("%s: %s %s\n",
           FUNCTION_NAME,
           "Error getting basic field value:",
           memberName ? memberName : "");
    return RTI_FALSE;
}

/**
 * @brief Gets the sequence length by sequence name. A DynamicData sample is
 * used to store this information.
 *
 * The structure of the data is stored in a DynamicData sample, so it can be
 * used to know the metadata of a specific PDU: the members it has, the
 * alignment and the size of each member.
 *
 * seqList is used as a dictionary to has the information that is needed such as
 * the kind of the member or the alignment.
 *
 * @param pulLength the size of the seq.(OUT)
 * @param dynData, the dynamic data sample used to obtain the size of the Seq by
 * SeqName. (IN)
 * @param pSeqName, the Seq name used to look up the size of the seq (IN)
 * @param align 0 is no alignment is setted. >0 otherwise. (OUT)
 *
 * @return True if the seq name exists and the length is returned. False
 * otherwise
 */
RTIBool getSeqLen(
        DDS_UnsignedLong *pulLength,
        struct DDS_DynamicData *dynData,
        const char *pSeqName,
        int *align = 0);
RTIBool getSeqLen(
        DDS_UnsignedLong *pulLength,
        struct DDS_DynamicData *dynData,
        const char *pSeqName,
        int *align)
{
    RTIBool retVal = RTI_FALSE;
    /* find pSeqName in SeqList, if found, get value from dynamic data */
    if (pSeqName != NULL && pulLength != NULL) {
        for (int i = 0; i < dim(seqList); i++) {
            if (strncmp(seqList[i].pSeqName,
                        pSeqName,
                        strlen(seqList[i].pSeqName))
                == 0) {
                if (align != NULL) {
                    *align = seqList[i].specialAlignment;
                }
                retVal = getValue(
                        dynData,
                        seqList[i].tk,
                        seqList[i].pSeqLenName,
                        DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                        (void*) pulLength);
                if (retVal == RTI_TRUE) {
                    return RTI_TRUE;
                }
            }
        }
#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("%s:Could not find %s \n", "getSeqLen", pSeqName);
#endif
    }
    return RTI_FALSE;
}

RTIBool serializeBasicField(
        struct DDS_DynamicData *sample, /* In */
        DDS_Char *stream,               /* Out */
        DDS_TCKind memberKind,
        DDS_TCKind elementKind,
        DDS_UnsignedLong memberLength,
        const DDS_Char *memberName,
        DDS_DynamicDataMemberId memberId,
        DDS_Long *bytesSerialized,
        RTI_RoutingServiceEnvironment *env,
        void *pValue)
{
    const DDS_Char FUNCTION_NAME[] = "serializeBasicField";
    DDS_ReturnCode_t retCode;
    *bytesSerialized = 0;

    if (sample != NULL) {
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("%s:Serializing %s ",
                   FUNCTION_NAME,
                   memberName ? memberName : "");
#endif
        switch (memberKind) {
        case DDS_TK_CHAR: {
            DDS_Char charValue;
            DDS_Char *charPtr = (DDS_Char*) stream;
            retCode = DDS_DynamicData_get_char(
                    sample,
                    &charValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
                *charPtr = charValue;
                *bytesSerialized = sizeof(DDS_Char);
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d (%x)\n", *charPtr, *charPtr);
#endif
            }
        } break;
        case DDS_TK_OCTET: {
            DDS_Octet octetValue;
            DDS_Octet *octetPtr = (DDS_Octet*) stream;
            retCode = DDS_DynamicData_get_octet(
                    sample,
                    &octetValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
                *octetPtr = octetValue;
                *bytesSerialized = sizeof(DDS_Octet);
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d (%x)\n", *octetPtr, *octetPtr);
#endif
            }
        } break;
        case DDS_TK_BOOLEAN: {
            DDS_Boolean boolValue;
            DDS_Boolean *boolPtr = (DDS_Boolean*) stream;
            retCode = DDS_DynamicData_get_octet(
                    sample,
                    &boolValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
                *boolPtr = boolValue;
                *bytesSerialized = sizeof(DDS_Boolean);
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d\n", *boolPtr);
#endif
            }
        } break;
        case DDS_TK_SHORT: {
            DDS_Short shortValue;
            DDS_Short *shortPtr = (DDS_Short*) stream;
            retCode = DDS_DynamicData_get_short(
                    sample,
                    &shortValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d (%x)\n", shortValue, shortValue);
#endif
                *shortPtr = htons(shortValue);
                /*                        *shortPtr = (shortValue); */
                *bytesSerialized = sizeof(DDS_Short);
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d (%x)\n", *shortPtr, *shortPtr);
#endif
            }
        } break;
        case DDS_TK_USHORT: {
            DDS_UnsignedShort uShortValue;
            DDS_UnsignedShort *uShortPtr = (DDS_UnsignedShort*) stream;

            retCode = DDS_DynamicData_get_ushort(
                    sample,
                    &uShortValue,
                    memberName,
                    memberId);
            if (strncmp(memberName,
                        "m_ui16AggStatePadding1",
                        strlen("m_ui16AggStatePadding1"))
                == 0) {
                /*
                 * if aligned at 2 byte boundary field does not exist
                 * otherwise
                 * it is present
                 */
                if (RTIOsapiAlignment_isAligned(stream, 2)) {
                    break;
                }
            }

            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %d (%x)\n", uShortValue, uShortValue);
#endif
                *uShortPtr = htons(uShortValue);
                *bytesSerialized = sizeof(DDS_UnsignedShort);
            }
        } break;
        case DDS_TK_ENUM:
        case DDS_TK_LONG: {
            DDS_Long longValue;
            DDS_Long *longPtr = (DDS_Long*) stream;
            retCode = DDS_DynamicData_get_long(
                    sample,
                    &longValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %ld (%8x)\n", longValue, longValue);
#endif
                /*                        printf ("Long Unswapped = %08x\n",*/
                /*                        longValue); */
                *longPtr = htonl(longValue);
                /*                        printf ("Long Swapped = %08x\n", */
                /*                        *longPtr); */
                *bytesSerialized = sizeof(DDS_Long);
            }
        } break;
        case DDS_TK_ULONG: {
            DDS_UnsignedLong uLongValue;
            DDS_UnsignedLong *uLongPtr = (DDS_UnsignedLong*) stream;
            retCode = DDS_DynamicData_get_ulong(
                    sample,
                    &uLongValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
                       /* printf ("ULong Unswapped = %08x\n", uLongValue); */
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %ld (%08x)\n", uLongValue, uLongValue);
#endif
                *uLongPtr = htonl(uLongValue);
                /*
                 *                        *uLongPtr =uLongValue;
                 *                        printf ("ULong Swapped = %08x\n",
                 *                        *uLongPtr);
                 */
                *bytesSerialized = sizeof(DDS_UnsignedLong);
            }
        } break;
        case DDS_TK_FLOAT: {
            DDS_Float floatValue;
            DDS_UnsignedLong *floatPtr = (DDS_UnsignedLong*) stream;
            retCode = DDS_DynamicData_get_float(
                    sample,
                    &floatValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %f\n", floatValue);
#endif
                *floatPtr = htonf(floatValue);
                *bytesSerialized = sizeof(DDS_Float);
            }
        } break;
        case DDS_TK_DOUBLE: {
            DDS_Double doubleValue;
            DDS_UnsignedLongLong *doublePtr = (DDS_UnsignedLongLong*) stream;
            retCode = DDS_DynamicData_get_double(
                    sample,
                    &doubleValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %f \n", doubleValue);
#endif
                *doublePtr = htond(doubleValue);
                *bytesSerialized = sizeof(DDS_Double);
            }
            break;
        } break;
        case DDS_TK_STRING: {
            /* The middleware will allocate the string for us */
            DDS_Char *stringValue = NULL;
            DDS_UnsignedLong length = memberLength;
            DDS_Char *charPtr = (DDS_Char*) stream;
            retCode = DDS_DynamicData_get_string(
                    sample,
                    &stringValue,
                    &length,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
                strncpy(charPtr, stringValue, memberLength);
                *bytesSerialized = memberLength;
                /* Free the allocated string */
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %s\n", stringValue);
#endif
                DDS_String_free(stringValue);
            }
        } break;

        /** not supported types as they are not used in DIS IDL **/
        /* case DDS_TK_BOOLEAN:
         *    RTI_RoutingServiceEnvironment_set_error(
         *            env, "Type of field %s not supported (boolean)",
         *            memberName?memberName:"");
         *    goto error;
         *    break;
         */
        case DDS_TK_WCHAR:
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Type of field %s not supported (wchar)",
                    memberName ? memberName : "");
            goto error;
            break;
        case DDS_TK_LONGLONG: {
            DDS_LongLong longLongValue;
            DDS_LongLong *longLongPtr = (DDS_LongLong*) stream;
            retCode = DDS_DynamicData_get_longlong(
                    sample,
                    &longLongValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %lld (%llx)\n",
                           longLongValue,
                           longLongValue);
#endif
                *longLongPtr = htonll(longLongValue);
                *bytesSerialized = sizeof(DDS_LongLong);
            }
        } break;
        case DDS_TK_ULONGLONG: {
            DDS_UnsignedLongLong uLongLongValue;
            DDS_UnsignedLongLong *uLongLongPtr = (DDS_UnsignedLongLong*) stream;
            retCode = DDS_DynamicData_get_ulonglong(
                    sample,
                    &uLongLongValue,
                    memberName,
                    memberId);
            if (retCode == DDS_RETCODE_OK) {
#ifdef ENABLE_DIS_DEBUG_MSGS
                if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                    printf("value: %lld\n", uLongLongValue);
#endif
                *uLongLongPtr = htonll(uLongLongValue);
                *bytesSerialized = sizeof(DDS_UnsignedLongLong);
            }
        } break;
        case DDS_TK_LONGDOUBLE:
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Type of field %s not supported (DDS_LongDouble)",
                    memberName ? memberName : "");
            goto error;
            break;
        case DDS_TK_ARRAY: {
            if (elementKind == DDS_TK_OCTET) {
                DDS_Octet *octetPtr = (DDS_Octet*) stream;
                retCode = DDS_DynamicData_get_octet_array(
                        sample,
                        octetPtr,
                        &memberLength,
                        memberName,
                        memberId);
                if (retCode == DDS_RETCODE_OK) {
                    *bytesSerialized = memberLength * sizeof(DDS_Octet);
                }
            } else if (elementKind == DDS_TK_CHAR) {
                DDS_Char *charPtr = (DDS_Char*) stream;
                retCode = DDS_DynamicData_get_char_array(
                        sample,
                        charPtr,
                        &memberLength,
                        memberName,
                        memberId);
                if (retCode == DDS_RETCODE_OK) {
                    *bytesSerialized = memberLength * sizeof(DDS_Char);
                }
            } else {
                RTI_RoutingServiceEnvironment_set_error(
                        env,
                        "Type of field %s not supported (array)",
                        memberName ? memberName : "");
                goto error;
            }
        } break;
        case DDS_TK_SEQUENCE:
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Type of field %s not supported (sequence)",
                    memberName ? memberName : "");
            goto error;
            break;
        case DDS_TK_WSTRING:
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Type of field %s not supported (wstring)",
                    memberName ? memberName : "");
            goto error;
            break;
        default:
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Unknown type for field %s",
                    memberName ? memberName : "");
            goto error;
            break;
        }
    } else {
        /* TBD sample was null do something */
        RTI_RoutingServiceEnvironment_set_error(env, "Sample is NULL");
        goto error;
    }

    /*
    printf("%s: %s %s\n", FUNCTION_NAME, "Successfully serialized basic field:",
    memberName?memberName:"");
    */
    return RTI_TRUE;

error:
    fprintf(stderr, "%s: %s %s\n",
           FUNCTION_NAME,
           "Error serializing basic field:",
           memberName ? memberName : "");
    return RTI_FALSE;
}

RTIBool serializeHeaderType(
        const struct DDS_TypeCode *tc,
        DDS_DynamicData *sample, /* In */
        DDS_Char *stream,        /* Out */
        DDS_UnsignedLong maxBuffLen,
        DDS_Long *totalBytesSerialized,
        RTI_RoutingServiceEnvironment *env)
{
    const DDS_Char FUNCTION_NAME[] = "SerializeHeaderType";
    RTIBool success;
    DDS_Long bytesSerialized = 0;
    DDS_TCKind memberKind;
    DDS_TCKind elementKind;
    DDS_UnsignedLong memberLength;
    struct DDS_TypeCode *memberTc;
    DDS_ExceptionCode_t ex;
    const DDS_Char *memberName;
    DDS_Char *streamPtr = (DDS_Char*) stream;
    *totalBytesSerialized = 0;

    if (sample != NULL) {
        /* xx.01 Time Stamp (double) 8 */
        memberName = DDS_TypeCode_member_name(tc, 1, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        memberTc = DDS_TypeCode_member_type(tc, 1, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        isBasicTypeCode(
                memberTc,
                &memberKind,
                &elementKind,
                &memberLength,
                &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        success = serializeBasicField(
                sample,    /* In */
                streamPtr, /* Out */
                memberKind,
                elementKind,
                memberLength,
                memberName,
                DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                &bytesSerialized,
                env,
                NULL);

        /* increment buffPtr by size of field */
        if (success != RTI_TRUE) {
            goto error;
        }
        streamPtr += bytesSerialized;
        *totalBytesSerialized += bytesSerialized;

        /* xx.02 Vehicle ID (int4) 12 */
        memberName = DDS_TypeCode_member_name(tc, 2, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        memberTc = DDS_TypeCode_member_type(tc, 2, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        isBasicTypeCode(
                memberTc,
                &memberKind,
                &elementKind,
                &memberLength,
                &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        success = serializeBasicField(
                sample,    /* In */
                streamPtr, /* Out */
                memberKind,
                elementKind,
                memberLength,
                memberName,
                DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                &bytesSerialized,
                env,
                NULL);

        /* increment buffPtr by size of field */
        if (success != RTI_TRUE) {
            goto error;
        }
        streamPtr += bytesSerialized;
        *totalBytesSerialized += bytesSerialized;

        /* xx.03 CUCS ID (int4) 16 */
        memberName = DDS_TypeCode_member_name(tc, 3, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        memberTc = DDS_TypeCode_member_type(tc, 3, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        isBasicTypeCode(
                memberTc,
                &memberKind,
                &elementKind,
                &memberLength,
                &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        success = serializeBasicField(
                sample,    /* In */
                streamPtr, /* Out */
                memberKind,
                elementKind,
                memberLength,
                memberName,
                DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                &bytesSerialized,
                env,
                NULL);

        /* increment buffPtr by size of field */
        if (success != RTI_TRUE) {
            goto error;
        }
        streamPtr += bytesSerialized;
        *totalBytesSerialized += bytesSerialized;

    } else {
        /* TBD sample was null do something */
        RTI_RoutingServiceEnvironment_set_error(env, "Sample is NULL");
        goto error;
    }

    /*
    printf("%s: %s\n", FUNCTION_NAME, "Successfully serialized header type");
    */
    return RTI_TRUE;

error:
    *totalBytesSerialized = 0;
    fprintf(stderr, "%s: %s\n", FUNCTION_NAME, "Error serializing header type");
    return RTI_FALSE;
}

DDS_Long serializeFields(
        const struct DDS_TypeCode *tc,
        DDS_DynamicData *sample, /* In */
        DDS_DynamicData *parent, /* In */
        DDS_Char *stream,        /* Out */
        DDS_UnsignedLong maxBuffLen,
        RTI_RoutingServiceEnvironment *env,
        const char *seqName)
{
    const DDS_Char FUNCTION_NAME[] = "serializeFields";
    DDS_TCKind kind, memberKind, elementKind;
    DDS_UnsignedLong memberLength;
    struct DDS_TypeCode *baseTc, *memberTc, *aliasTc;
    DDS_ExceptionCode_t ex;
    DDS_UnsignedLong memberCount, i;
    const DDS_Char *memberName;
    const DDS_Char *typeName;
    DDS_Boolean memberExists;
    DDS_DynamicData memberDynData;
    DDS_DynamicData *memberDynDataPtr;
    DDS_ReturnCode_t retCode;
    RTIBool isBasicTc;
    DDS_Long bytesSerialized = 0;
    DDS_Long totalBytesSerialized = 0;

    kind = DDS_TypeCode_kind(tc, &ex);
    CHECK_TYPECODE_OP(ex, goto error);

    switch (kind) {
    case DDS_TK_ALIAS: {
        aliasTc = DDS_TypeCode_content_type(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        if ((bytesSerialized = serializeFields(
                     aliasTc,
                     sample,
                     parent,
                     &stream[totalBytesSerialized],
                     maxBuffLen,
                     env))
            == 0) {
            totalBytesSerialized = 0;
            goto error;
        } else {
            totalBytesSerialized += bytesSerialized;
        }
    } break;
    case DDS_TK_UNION:
    case DDS_TK_SPARSE:
    case DDS_TK_VALUE:
    case DDS_TK_STRUCT: {
        if (kind == DDS_TK_VALUE || kind == DDS_TK_SPARSE) {
            baseTc = DDS_TypeCode_concrete_base_type(tc, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            if (baseTc != NULL) {
                if ((bytesSerialized = serializeFields(
                             baseTc,
                             sample,
                             parent,
                             &stream[totalBytesSerialized],
                             maxBuffLen,
                             env))
                    == 0) {
                    totalBytesSerialized = 0;
                    goto error;
                } else {
                    totalBytesSerialized += bytesSerialized;
                }
            }
        }

        memberCount = DDS_TypeCode_member_count(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        typeName = DDS_TypeCode_name(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        for (i = 0; i < memberCount; i++) {
            memberName = DDS_TypeCode_member_name(tc, i, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            memberTc = DDS_TypeCode_member_type(tc, i, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            if (sample != NULL) {
                memberExists = DDS_DynamicData_member_exists(
                        sample,
                        memberName,
                        DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);
            } else {
                memberExists = DDS_BOOLEAN_FALSE;
            }

            isBasicTc = isBasicTypeCode(
                    memberTc,
                    &memberKind,
                    &elementKind,
                    &memberLength,
                    &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            if (isBasicTc) {
                if (!serializeBasicField(
                            memberExists ? sample : NULL,
                            &stream[totalBytesSerialized],
                            memberKind,
                            elementKind,
                            memberLength,
                            memberName,
                            DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                            &bytesSerialized,
                            env,
                            NULL)) {
                    totalBytesSerialized = 0;
                    goto error;
                } else {
                    totalBytesSerialized += bytesSerialized;
                }
            } else {
                if (memberExists) {
                    DDS_DynamicData_initialize(
                            &memberDynData,
                            NULL,
                            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);

                    retCode = DDS_DynamicData_get_complex_member(
                            sample,
                            &memberDynData,
                            memberName,
                            DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    memberDynDataPtr = &memberDynData;
                    parent = sample;
                } else {
                    memberDynDataPtr = NULL;
                }
                bytesSerialized = serializeFields(
                        memberTc,
                        memberDynDataPtr,
                        parent,
                        &stream[totalBytesSerialized],
                        maxBuffLen,
                        env,
                        memberName);
                totalBytesSerialized += bytesSerialized;

                if (memberDynDataPtr != NULL) {
                    DDS_DynamicData_finalize(memberDynDataPtr);
                    memberDynDataPtr = NULL;
                }
            }
        }
    } break;
    case DDS_TK_ARRAY:
    case DDS_TK_SEQUENCE: {
        DDS_TypeCode *elementTc;
        DDS_UnsignedLong elementCount, maxElementCount, dimensionsCount,
                memberId = 0;
        int align = 0;

        elementTc = DDS_TypeCode_content_type(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);
        /* memberName = DDS_TypeCode_name(elementTc, &ex); */
        /* CHECK_TYPECODE_OP(ex,goto error); */
        if (kind == DDS_TK_ARRAY) {
            dimensionsCount = DDS_TypeCode_array_dimension_count(tc, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            elementCount = 1;

            for (i = 0; i < dimensionsCount; i++) {
                elementCount *= DDS_TypeCode_array_dimension(tc, i, &ex);
                CHECK_TYPECODE_OP(ex, goto error);
            }

        } else {
            DDS_UnsignedLong userElementCount;
            elementCount = DDS_DynamicData_get_member_count(sample); /* gives
                                                                      * the
                                                                      * sequence's
                                                                      * member
                                                                      * count
                                                                      */
            maxElementCount = DDS_TypeCode_length(tc, &ex);  /*
                                                              * returns max seq
                                                              * len
                                                              */
            if (!getSeqLen(&userElementCount, parent, seqName, &align)) {
                getSeqLen(&userElementCount, sample, seqName, &align);
            }

            if (userElementCount != elementCount)
                fprintf(stderr,
                        "The DDS sequence (%u) size dose not match the sequence "
                        "size in the PDU packet (%u), using DDS sequence "
                        "size.\n",
                        elementCount,
                        userElementCount);

            if (elementCount > maxElementCount) {
                elementCount = maxElementCount;
            }
        }

        isBasicTc = isBasicTypeCode(
                elementTc,
                &memberKind,
                &elementKind,
                &memberLength,
                &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        for (i = 0; i < elementCount; i++) {
            memberId = i + 1;

            if (isBasicTc) {
                if ((bytesSerialized = serializeBasicField(
                             (i < elementCount) ? sample : NULL,
                             &stream[totalBytesSerialized],
                             memberKind,
                             elementKind,
                             memberLength,
                             NULL,
                             memberId,
                             &bytesSerialized,
                             env,
                             NULL))) {
                    goto error;
                }
                totalBytesSerialized += bytesSerialized;
            } else {
                if (sample != NULL && i < elementCount) {
                    DDS_DynamicData_initialize(
                            &memberDynData,
                            NULL,
                            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);

                    retCode = DDS_DynamicData_bind_complex_member(
                            sample,
                            &memberDynData,
                            NULL,
                            memberId);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    memberDynDataPtr = &memberDynData;
                } else {
                    memberDynDataPtr = NULL;
                }

                if ((bytesSerialized = serializeFields(
                             elementTc,
                             memberDynDataPtr,
                             sample,
                             &stream[totalBytesSerialized],
                             maxBuffLen,
                             env))
                    == 0) {
                    goto error;
                }
                totalBytesSerialized += bytesSerialized;

                if (memberDynDataPtr != NULL) {
                    retCode = DDS_DynamicData_unbind_complex_member(
                            sample,
                            memberDynDataPtr);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    DDS_DynamicData_finalize(memberDynDataPtr);
                    memberDynDataPtr = NULL;
                }
            }
        }  /* for array/seq members */
        if (align != 0) {
            int padBytes = ((align - 1) - ((size_t) stream % align));
            for (int j = 0; j < padBytes; ++j) {
                stream[totalBytesSerialized] = 0;
                ++totalBytesSerialized;
            }
        }
    } break;
    default: {
        goto error;
    } break;
    }

    return totalBytesSerialized;
error:
    fprintf(stderr, "%s: %s\n", FUNCTION_NAME, "Error serializing DDS Data");
    return totalBytesSerialized;
}

/**
 *
 * @brief Serializes a dynamic data sample into the provided stream.
 *
 * @param sample The data sample to be serialized
 * @param stream The streamto serialize into
 * @param maxBuffLen The maximum length of the stream
 * @param env The environment to report error messages
 *
 * @return 0 if error, otherwise number of bytes serialized
 *
 */
RTI_INT32 DisSerializer_serializeSample(
        DDS_DynamicData *sample,
        DDS_Char *stream,
        RTI_UINT32 maxStreamLen,
        RTI_RoutingServiceEnvironment *env)
{
    const DDS_Char FUNCTION_NAME[] = "SerializeSample";
    const struct DDS_TypeCode *tc;
    DDS_Long bytesSerialized = 0;

    tc = DDS_DynamicData_get_type(sample);

    if (tc == NULL) {
        goto error;
    }

    if ((bytesSerialized =
                 serializeFields(tc, sample, NULL, stream, maxStreamLen, env))
        == 0) {
        goto error;
    }

    return bytesSerialized;

error:
    fprintf(stderr, "%s: %s\n", FUNCTION_NAME, "Error serializing DDS data");
    return bytesSerialized;
}

RTIBool deserializeBasicField(
        DDS_DynamicData *sample,
        DDS_TCKind memberKind,
        DDS_TCKind elementKind,
        DDS_UnsignedLong memberLength,
        const DDS_Char *memberName,
        DDS_DynamicDataMemberId memberId,
        DDS_Char *stream,
        DDS_Long *totalBytesRead)
{
    const DDS_Char FUNCTION_NAME[] = "deserializeBasicField";
    DDS_ReturnCode_t retCode;

    *totalBytesRead = 0;

#ifdef ENABLE_DIS_DEBUG_MSGS
    if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
        printf("%s:Deserializing %s ", FUNCTION_NAME, memberName);
#endif
    switch (memberKind) {
    case DDS_TK_CHAR: {
        DDS_Char *charPtr = (DDS_Char*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %d\n", *charPtr);
#endif
        retCode = DDS_DynamicData_set_char(
                sample,
                memberName,
                memberId,
                *charPtr);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Char);
    } break;
    case DDS_TK_OCTET: {
        DDS_Octet *octetPtr = (DDS_Octet*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %d\n", *octetPtr);
#endif
        retCode = DDS_DynamicData_set_octet(
                sample,
                memberName,
                memberId,
                *octetPtr);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Octet);
    } break;
    case DDS_TK_BOOLEAN: {
        DDS_Boolean *boolPtr = (DDS_Boolean*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %d\n", *boolPtr);
#endif
        retCode = DDS_DynamicData_set_boolean(
                sample,
                memberName,
                memberId,
                *boolPtr);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Boolean);
    } break;
    case DDS_TK_ENUM: {
        /*
           KLUDGE there is one enum field (300.07) in the
           DIS message set that is 2 bytes instead of 1.
        */
        if (!strcmp(memberName, "payloadType")) {
            DDS_UnsignedShort *uShortPtr = (DDS_UnsignedShort*) stream;
            retCode = DDS_DynamicData_set_long(
                    sample,
                    memberName,
                    memberId,
                    (DDS_Long) ntohs(*uShortPtr));
            if (retCode != DDS_RETCODE_OK) {
                goto error;
            }
            *totalBytesRead = sizeof(DDS_UnsignedShort);
        } else {
            DDS_Char *uCharPtr = (DDS_Char*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
            if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                printf("value: %ud\n", *uCharPtr);
#endif
            /* need ntohl */
            retCode = DDS_DynamicData_set_long(
                    sample,
                    memberName,
                    memberId,
                    (DDS_Long) *uCharPtr);
            if (retCode != DDS_RETCODE_OK) {
                goto error;
            }
            *totalBytesRead = sizeof(DDS_Char);
        }


    } break;
    case DDS_TK_SHORT: {
        DDS_Short *shortPtr = (DDS_Short*) stream;
        DDS_Short value = ntohs(*shortPtr);
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %d\n", value);
#endif
        retCode =
                DDS_DynamicData_set_short(sample, memberName, memberId, value);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Short);
    } break;
    case DDS_TK_USHORT: {
        DDS_UnsignedShort *uShortPtr = (DDS_UnsignedShort*) stream;
        DDS_UnsignedShort value = ntohs(*uShortPtr);
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %d\n", value);
#endif
        retCode =
                DDS_DynamicData_set_ushort(sample, memberName, memberId, value);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        if (strncmp(memberName,
                    "m_ui16AggStatePadding1",
                    strlen("m_ui16AggStatePadding1"))
            == 0) {
            /*
             * if aligned at 2 byte boundary field does not exist otherwise it
             * is present
             */
            if (RTIOsapiAlignment_isAligned(stream, 2)) {
                /*                    if ((int)stream % 2 == 0) */
                break;
            }
        }
        *totalBytesRead = sizeof(DDS_UnsignedShort);
    } break;
    case DDS_TK_LONG: {
        DDS_Long *longPtr = (DDS_Long*) stream;
        DDS_Long value = ntohl(*longPtr);
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %ld\n", value);
#endif
        retCode = DDS_DynamicData_set_long(sample, memberName, memberId, value);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Long);
    } break;
    case DDS_TK_ULONG: {
        DDS_UnsignedLong *uLongPtr = (DDS_UnsignedLong*) stream;
        DDS_UnsignedLong value = ntohl(*uLongPtr);
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %lu\n", value);
#endif
        retCode =
                DDS_DynamicData_set_ulong(sample, memberName, memberId, value);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_UnsignedLong);
    } break;

    case DDS_TK_FLOAT: {
        /* memcpy into a primative (long) in case of alignment of stream */
        DDS_UnsignedLong buffer;
        memcpy(&buffer, (char*) stream, sizeof(DDS_Float));
        DDS_Float value = (DDS_Float) ntohf(buffer);

#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %f\n size: %lu ", value, sizeof(DDS_Float));
#endif
        retCode =
                DDS_DynamicData_set_float(sample, memberName, memberId, value);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Float);
    } break;
    case DDS_TK_DOUBLE: {
        DDS_UnsignedLongLong buffer;
        memcpy(&buffer, (char*) stream, sizeof(DDS_UnsignedLongLong));
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %.4f\n", ntohd(buffer));
#endif
        retCode = DDS_DynamicData_set_double(
                sample,
                memberName,
                memberId,
                ntohd(buffer));
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_Double);
    } break;

        /* comment out */
    case DDS_TK_STRING: {
        DDS_Char *charPtr = (DDS_Char*) stream;
        DDS_UnsignedLong lLen;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %s\n", charPtr);
#endif
        if (memberLength > strlen(stream))
            lLen = strlen(stream);
        else
            lLen = memberLength;
        retCode = DDS_DynamicData_set_string(
                sample,
                memberName,
                memberId,
                charPtr);
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = lLen;
    } break;

    /** not supported types as they are not used in DIS IDL **/
    /*
     * case DDS_TK_BOOLEAN:
     *    fprintf(stderr, "Type of field %s not supported (boolean)",
     *    memberName?memberName:""); goto error; break;
     */
    case DDS_TK_WCHAR:
        printf("Type of field %s not supported (wchar)",
               memberName ? memberName : "");
        goto error;
        break;
    case DDS_TK_LONGLONG: {
        DDS_LongLong *LongLongPtr = (DDS_LongLong*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %lld\n", ntohll(*LongLongPtr));
#endif
        retCode = DDS_DynamicData_set_longlong(
                sample,
                memberName,
                memberId,
                ntohll(*LongLongPtr));
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_LongLong);
    } break;

    case DDS_TK_ULONGLONG: {
        DDS_UnsignedLongLong *uLongLongPtr = (DDS_UnsignedLongLong*) stream;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("value: %llu\n", ntohll(*uLongLongPtr));
#endif
        retCode = DDS_DynamicData_set_ulonglong(
                sample,
                memberName,
                memberId,
                ntohll(*uLongLongPtr));
        if (retCode != DDS_RETCODE_OK) {
            goto error;
        }
        *totalBytesRead = sizeof(DDS_UnsignedLongLong);
    } break;

    case DDS_TK_LONGDOUBLE:
        fprintf(stderr, "Type of field %s not supported (DDS_LongDouble)",
               memberName ? memberName : "");
        goto error;
        break;
    case DDS_TK_ARRAY: {
        if (elementKind == DDS_TK_OCTET) {
            DDS_Octet *octetPtr = (DDS_Octet*) stream;
            retCode = DDS_DynamicData_set_octet_array(
                    sample,
                    memberName,
                    memberId,
                    memberLength,
                    octetPtr);
            if (retCode != DDS_RETCODE_OK) {
                goto error;
            }
            *totalBytesRead = memberLength;
        } else if (elementKind == DDS_TK_CHAR) {
            DDS_Char *charPtr = (DDS_Char*) stream;
            retCode = DDS_DynamicData_set_char_array(
                    sample,
                    memberName,
                    memberId,
                    memberLength,
                    charPtr);
            if (retCode != DDS_RETCODE_OK) {
                goto error;
            }
            *totalBytesRead = memberLength;
        } else {
            fprintf(stderr, "Type of field %s not supported (array)",
                   memberName ? memberName : "");
            goto error;
        }
    } break;
    case DDS_TK_SEQUENCE:
        fprintf(stderr, "Type of field %s not supported (sequence)",
               memberName ? memberName : "");
        goto error;
        break;
    case DDS_TK_WSTRING:
        fprintf(stderr, "Type of field %s not supported (wstring)",
               memberName ? memberName : "");
        goto error;
        break;
    default:
        fprintf(stderr,
                "Unknown type for field %s",
                memberName ? memberName : "");
        goto error;
        break;
    }

    /*
     * printf("%s: %s %s\n", FUNCTION_NAME, "Successfully deserialized record,
     * setting basic field:", memberName?memberName:"");
     */
    return RTI_TRUE;

error:
    fprintf(stderr, "%s: %s %s\n",
           FUNCTION_NAME,
           "Error deserializing record, setting basic field:",
           memberName ? memberName : "");
    *totalBytesRead = 0;
    return RTI_FALSE;
}

void DDS_XMLTypeCode_get_basic_typename(
        struct DDS_TypeCode *src,
        const char **dstName)
{
    DDS_TCKind kind;
    DDS_ExceptionCode_t ex;
    const char *METHOD_NAME = "DDS_XMLTypeCode_get_basic_typename";

    kind = DDS_TypeCode_kind(src, &ex);
    switch (kind) {
    case DDS_TK_SHORT:
        *dstName = "short";
        break;
    case DDS_TK_LONG:
        *dstName = "long";
        break;
    case DDS_TK_USHORT:
        *dstName = "unsignedShort";
        break;
    case DDS_TK_ULONG:
        *dstName = "unsignedLong";
        break;
    case DDS_TK_FLOAT:
        *dstName = "float";
        break;
    case DDS_TK_DOUBLE:
        *dstName = "double";
        break;
    case DDS_TK_BOOLEAN:
        *dstName = "boolean";
        break;
    case DDS_TK_CHAR:
        *dstName = "char";
        break;
    case DDS_TK_OCTET:
        *dstName = "octet";
        break;
    case DDS_TK_LONGLONG:
        *dstName = "longLong";
        break;
    case DDS_TK_ULONGLONG:
        *dstName = "unsignedLongLong";
        break;
    case DDS_TK_LONGDOUBLE:
        *dstName = "longDouble";
        break;
    case DDS_TK_WCHAR:
        *dstName = "wchar";
        break;
    case DDS_TK_STRING:
        *dstName = "string";
        break;
    case DDS_TK_WSTRING:
        *dstName = "wstring";
        break;
    case DDS_TK_NULL:
        *dstName = "-NULL-";
        break;
    default:
        *dstName = NULL;
        break;
    }
}

RTIBool deserializeFields(
        const struct DDS_TypeCode *tc,
        DDS_DynamicData *sample,  /* Out */
        DDS_DynamicData *parent,  /* Out */
        DDS_Char *stream,         /* In */
        DDS_Long *totalBytesRead, /* Out */
        DDS_Long seqNumber,
        const char *seqName)
{
    const DDS_Char FUNCTION_NAME[] = "deserializeFields";
    DDS_TCKind kind, memberKind, elementKind;
    DDS_UnsignedLong memberLength;
    const struct DDS_TypeCode *baseTc, *memberTc, *aliasTc;
    DDS_ExceptionCode_t ex;
    DDS_UnsignedLong memberCount, i, elementCount = 0;
    const DDS_Char *memberName = NULL;
    const DDS_Char *typeName;
    DDS_DynamicDataMemberId memberId = DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED;
    DDS_DynamicData memberDynData, seqDynData;
    DDS_DynamicData *memberDynDataPtr, *seqDynDataPtr;
    DDS_ReturnCode_t retCode;
    RTIBool isBasicTc;
    DDS_UnsignedLong memberIndex = 0;
    DDS_Boolean isMemberKey;

    DDS_Long bytesRead = 0;
    *totalBytesRead = 0;

    kind = DDS_TypeCode_kind(tc, &ex);
    CHECK_TYPECODE_OP(ex, goto error);

    switch (kind) {
    case DDS_TK_ALIAS: {
        aliasTc = DDS_TypeCode_content_type(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        if (!deserializeFields(
                    aliasTc,
                    sample,
                    NULL,
                    &stream[*totalBytesRead],
                    &bytesRead)) {
            goto error;
        } else {
            /* update bytes read */
            *totalBytesRead += bytesRead;
        }
    } break;

    case DDS_TK_SPARSE:
    case DDS_TK_VALUE:
    case DDS_TK_STRUCT: {
        if (kind == DDS_TK_VALUE || kind == DDS_TK_SPARSE) {
            baseTc = DDS_TypeCode_concrete_base_type(tc, &ex);

            CHECK_TYPECODE_OP(ex, goto error);

            if (baseTc != NULL /* also check kind not TK_NULL */) {
                if (!deserializeFields(
                            baseTc,
                            sample,
                            NULL,
                            &stream[*totalBytesRead],
                            &bytesRead)) {
                    goto error;
                } else {
                    /* update bytes read*/
                    *totalBytesRead += bytesRead;
                }
            }
        }

        memberCount = DDS_TypeCode_member_count(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

        typeName = DDS_TypeCode_name(tc, &ex);
        CHECK_TYPECODE_OP(ex, goto error);

#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("%s:Deserializing Structure %s \n", FUNCTION_NAME, typeName);
#endif

        for (i = 0; i < memberCount; i++) {
            memberTc = DDS_TypeCode_member_type(tc, i, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            memberName = DDS_TypeCode_member_name(tc, i, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            isMemberKey = DDS_TypeCode_is_member_key(tc, i, &ex);
            CHECK_TYPECODE_OP(ex, goto error);

            isBasicTc = isBasicTypeCode(
                    memberTc,
                    &memberKind,
                    &elementKind,
                    &memberLength,
                    &ex);
            CHECK_TYPECODE_OP(ex, goto error);
            if (isBasicTc) {
                if (!deserializeBasicField(
                            sample,
                            memberKind,
                            elementKind,
                            memberLength,
                            memberName,
                            DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED,
                            &stream[*totalBytesRead],
                            &bytesRead)) {
                    goto error;
                } else {
                    *totalBytesRead += bytesRead;
                }
            } else {
                if (sample != NULL) {
                    DDS_DynamicData_initialize(
                            &memberDynData,
                            NULL,
                            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);

#ifdef ENABLE_DIS_DEBUG_MSGS
                    if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                        printf("\n%s:Binding complex member %s\n",
                               FUNCTION_NAME,
                               memberName);
#endif
                    retCode = DDS_DynamicData_bind_complex_member(
                            sample,
                            &memberDynData,
                            memberName,
                            DDS_DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    memberDynDataPtr = &memberDynData;
                } else {
                    memberDynDataPtr = NULL;
                }
                if (!deserializeFields(
                            memberTc,
                            memberDynDataPtr,
                            sample,
                            &stream[*totalBytesRead],
                            &bytesRead,
                            i,
                            memberName)) {
                    goto error;
                } else {
                    /* update bytes read*/
                    *totalBytesRead += bytesRead;
                }

                if (memberDynDataPtr != NULL) {
                    retCode = DDS_DynamicData_unbind_complex_member(
                            sample,
                            memberDynDataPtr);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    DDS_DynamicData_finalize(memberDynDataPtr);
                    memberDynDataPtr = NULL;
                }
            }
        }
    } break;

    case DDS_TK_SEQUENCE: {
        int specialAlignment = 0;
        DDS_UnsignedLong seqLen = 0;
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("%s:Processing Sequence\n", FUNCTION_NAME);
#endif
        baseTc = DDS_TypeCode_content_type(tc, &ex);
        /*           CHECK_TYPECODE_OP(ex,goto error); */
        if (ex != DDS_NO_EXCEPTION_CODE)
            baseTc = tc;
        isBasicTc = isBasicTypeCode(
                baseTc,
                &memberKind,
                &elementKind,
                &memberLength,
                &ex);

        if (!getSeqLen(&seqLen, parent, seqName, &specialAlignment)) {
            getSeqLen(&seqLen, sample, seqName, &specialAlignment);
        }

        for (int x = 0; x < seqLen; x++) {
            if (isBasicTc) {
                if (!deserializeBasicField(
                            sample,
                            memberKind,
                            elementKind,
                            memberLength,
                            NULL,
                            /*seqName,*/ x + 1,
                            &stream[*totalBytesRead],
                            &bytesRead)) {
                    goto error;
                } else {
                    *totalBytesRead += bytesRead;
                }
            } else {
                if (sample != NULL) {
                    DDS_DynamicData_initialize(
                            &seqDynData,
                            NULL,
                            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);

#ifdef ENABLE_DIS_DEBUG_MSGS
                    if (_verbosity >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
                        printf("\n%s:Binding complex member (seq) %d[%d]\n",
                               FUNCTION_NAME,
                               seqNumber,
                               x);
#endif
                    /*
                     * NOTE: bind_complex_member can't bind a sequence by name.
                     *       it must use the member_id.  This is 1-based member
                     *       number.
                     */
                    retCode = DDS_DynamicData_bind_complex_member(
                            sample,
                            &seqDynData,
                            NULL,
                            x + 1);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    seqDynDataPtr = &seqDynData;
                } else {
                    seqDynDataPtr = NULL;
                }
                if (!deserializeFields(
                            baseTc,
                            seqDynDataPtr,
                            sample,
                            &stream[*totalBytesRead],
                            &bytesRead)) {
                    goto error;
                } else {
                    /* update bytes read*/
                    *totalBytesRead += bytesRead;
                }

                if (seqDynDataPtr != NULL) {
                    retCode = DDS_DynamicData_unbind_complex_member(
                            sample,
                            seqDynDataPtr);

                    if (retCode != DDS_RETCODE_OK) {
                        goto error;
                    }

                    DDS_DynamicData_finalize(seqDynDataPtr);
                    seqDynDataPtr = NULL;
                }
            }
        }  /* for seq members */
        if (specialAlignment != 0) {
            /*
             * can't use
             * stream = RTIOsapiAlignment_alignAddressUp(stream,
             * specialAlignment);
             * because we want to change the index (bytesRead), not the stream
             * pointer
             *
             *  *totalBytesRead = *totalBytesRead
             *      + ((specialAlignment - 1)
             *          - ((size_t) stream % specialAlignment));
             */
        }
    } break;

    case DDS_TK_ARRAY:
        fprintf(stderr, "DDS_TK_ARRAY not tested\n");
        break;

    case DDS_TK_UNION:
        fprintf(stderr, "DDS_TK_UNION not supported\n");
    default: {
        goto error;
    } break;
    }

    return RTI_TRUE;

error:
    fprintf(stderr, "%s: %s%s\n",
           FUNCTION_NAME,
           "Error deserializing field ",
           memberName);
    return RTI_FALSE;
}

RTIBool DisSerializer_deserializeSample(
        DDS_DynamicData *sample,
        DDS_Char *stream,
        DDS_Long *bytesRead)
{
    const DDS_Char FUNCTION_NAME[] = "DeserializeSample";
    const struct DDS_TypeCode *tc;
    DDS_ReturnCode_t retCode;

    printf("%s: %s\n", FUNCTION_NAME, "Deserializing sample");

    tc = DDS_DynamicData_get_type(sample);

    if (tc == NULL) {
        goto error;
    }

    retCode = DDS_DynamicData_clear_all_members(sample);

    if (retCode != DDS_RETCODE_OK) {
        goto error;
    }

    if (!deserializeFields(tc, sample, NULL, stream, bytesRead)) {
        goto error;
    }

    fprintf(stderr, "%s: Sample deserialized, %d bytes read\n",
           FUNCTION_NAME,
           *bytesRead);

    return RTI_TRUE;
error:
    fprintf(stderr, "%s: Error deserializing sample, %d bytes read\n",
           FUNCTION_NAME,
           *bytesRead);
    return RTI_FALSE;
}
