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

/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from HeaderPDU.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef HeaderPDU_1219617298_h
#define HeaderPDU_1219617298_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


#include "DIS_Data_Type.h"


#ifdef __cplusplus
extern "C" {
#endif


extern const char* DIS_PDU_HeaderTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_PDU_HeaderSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_PDU_HeaderTypeSupport;
class DIS_PDU_HeaderDataWriter;
class DIS_PDU_HeaderDataReader;
    #endif

#endif


class DIS_PDU_Header {
public:
#ifdef __cplusplus
    typedef struct DIS_PDU_HeaderSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_PDU_HeaderTypeSupport TypeSupport;
    typedef DIS_PDU_HeaderDataWriter DataWriter;
    typedef DIS_PDU_HeaderDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_ui8ProtocolVersion;

    DIS_DATA_TYPE_KUINT8 m_ui8ExerciseID;

    DIS_DATA_TYPE_KUINT8 m_ui8PDUType;

    DIS_DATA_TYPE_KUINT8 m_ui8ProtocolFamily;

    DIS_DATA_TYPE_TimeStamp m_TimeStamp;

    DIS_DATA_TYPE_KUINT16 m_ui16PDULength;

    DIS_DATA_TYPE_KUINT8 m_ui8Padding1;

    DIS_DATA_TYPE_KUINT8 m_ui8Padding2;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode* DIS_PDU_Header_get_typecode(void); /* Type code
                                                                    */


DDS_SEQUENCE(DIS_PDU_HeaderSeq, DIS_PDU_Header);

NDDSUSERDllExport RTIBool DIS_PDU_Header_initialize(DIS_PDU_Header* self);

NDDSUSERDllExport RTIBool DIS_PDU_Header_initialize_ex(
        DIS_PDU_Header* self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_PDU_Header_finalize(DIS_PDU_Header* self);

NDDSUSERDllExport void DIS_PDU_Header_finalize_ex(
        DIS_PDU_Header* self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool
DIS_PDU_Header_copy(DIS_PDU_Header* dst, const DIS_PDU_Header* src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#endif /* HeaderPDU_1219617298_h */
