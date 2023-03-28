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

#ifndef DIS_Data_Type_526845752_h
#define DIS_Data_Type_526845752_h

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


typedef DDS_Octet DIS_DATA_TYPE_KUINT8;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUINT8_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KUINT8Seq, DIS_DATA_TYPE_KUINT8);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUINT8_initialize(DIS_DATA_TYPE_KUINT8 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT8_initialize_ex(
        DIS_DATA_TYPE_KUINT8 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT8_finalize(
        DIS_DATA_TYPE_KUINT8 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT8_finalize_ex(
        DIS_DATA_TYPE_KUINT8 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT8_copy(
        DIS_DATA_TYPE_KUINT8 *dst,
        const DIS_DATA_TYPE_KUINT8 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Octet DIS_DATA_TYPE_KINT8;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode* DIS_DATA_TYPE_KINT8_get_typecode(void); /* Type
                                                                           code
                                                                         */

DDS_SEQUENCE(DIS_DATA_TYPE_KINT8Seq, DIS_DATA_TYPE_KINT8);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KINT8_initialize(DIS_DATA_TYPE_KINT8* self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT8_initialize_ex(
        DIS_DATA_TYPE_KINT8 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT8_finalize(DIS_DATA_TYPE_KINT8 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT8_finalize_ex(
        DIS_DATA_TYPE_KINT8 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT8_copy(
        DIS_DATA_TYPE_KINT8 *dst,
        const DIS_DATA_TYPE_KINT8 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_UnsignedShort DIS_DATA_TYPE_KUINT16;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUINT16_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KUINT16Seq, DIS_DATA_TYPE_KUINT16);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUINT16_initialize(DIS_DATA_TYPE_KUINT16 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT16_initialize_ex(
        DIS_DATA_TYPE_KUINT16 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT16_finalize(
        DIS_DATA_TYPE_KUINT16 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT16_finalize_ex(
        DIS_DATA_TYPE_KUINT16 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT16_copy(
        DIS_DATA_TYPE_KUINT16 *dst,
        const DIS_DATA_TYPE_KUINT16 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Short DIS_DATA_TYPE_KINT16;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KINT16_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KINT16Seq, DIS_DATA_TYPE_KINT16);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KINT16_initialize(DIS_DATA_TYPE_KINT16 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT16_initialize_ex(
        DIS_DATA_TYPE_KINT16 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT16_finalize(
        DIS_DATA_TYPE_KINT16 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT16_finalize_ex(
        DIS_DATA_TYPE_KINT16 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT16_copy(
        DIS_DATA_TYPE_KINT16 *dst,
        const DIS_DATA_TYPE_KINT16 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_UnsignedLong DIS_DATA_TYPE_KUINT32;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUINT32_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KUINT32Seq, DIS_DATA_TYPE_KUINT32);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUINT32_initialize(DIS_DATA_TYPE_KUINT32 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT32_initialize_ex(
        DIS_DATA_TYPE_KUINT32 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT32_finalize(
        DIS_DATA_TYPE_KUINT32 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT32_finalize_ex(
        DIS_DATA_TYPE_KUINT32 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT32_copy(
        DIS_DATA_TYPE_KUINT32 *dst,
        const DIS_DATA_TYPE_KUINT32 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Long DIS_DATA_TYPE_KINT32;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KINT32_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KINT32Seq, DIS_DATA_TYPE_KINT32);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KINT32_initialize(DIS_DATA_TYPE_KINT32 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT32_initialize_ex(
        DIS_DATA_TYPE_KINT32 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT32_finalize(
        DIS_DATA_TYPE_KINT32 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT32_finalize_ex(
        DIS_DATA_TYPE_KINT32 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT32_copy(
        DIS_DATA_TYPE_KINT32 *dst,
        const DIS_DATA_TYPE_KINT32 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_UnsignedLongLong DIS_DATA_TYPE_KUINT64;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUINT64_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KUINT64Seq, DIS_DATA_TYPE_KUINT64);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUINT64_initialize(DIS_DATA_TYPE_KUINT64 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT64_initialize_ex(
        DIS_DATA_TYPE_KUINT64 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT64_finalize(
        DIS_DATA_TYPE_KUINT64 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUINT64_finalize_ex(
        DIS_DATA_TYPE_KUINT64 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUINT64_copy(
        DIS_DATA_TYPE_KUINT64 *dst,
        const DIS_DATA_TYPE_KUINT64 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_LongLong DIS_DATA_TYPE_KINT64;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KINT64_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KINT64Seq, DIS_DATA_TYPE_KINT64);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KINT64_initialize(DIS_DATA_TYPE_KINT64* self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT64_initialize_ex(
        DIS_DATA_TYPE_KINT64 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT64_finalize(
        DIS_DATA_TYPE_KINT64 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KINT64_finalize_ex(
        DIS_DATA_TYPE_KINT64 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KINT64_copy(
        DIS_DATA_TYPE_KINT64 *dst,
        const DIS_DATA_TYPE_KINT64 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Octet DIS_DATA_TYPE_KOCTET;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KOCTET_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KOCTETSeq, DIS_DATA_TYPE_KOCTET);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KOCTET_initialize(DIS_DATA_TYPE_KOCTET* self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KOCTET_initialize_ex(
        DIS_DATA_TYPE_KOCTET *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KOCTET_finalize(
        DIS_DATA_TYPE_KOCTET *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KOCTET_finalize_ex(
        DIS_DATA_TYPE_KOCTET *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KOCTET_copy(
        DIS_DATA_TYPE_KOCTET *dst,
        const DIS_DATA_TYPE_KOCTET *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Octet DIS_DATA_TYPE_KUOCTET;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUOCTET_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KUOCTETSeq, DIS_DATA_TYPE_KUOCTET);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUOCTET_initialize(DIS_DATA_TYPE_KUOCTET *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUOCTET_initialize_ex(
        DIS_DATA_TYPE_KUOCTET *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUOCTET_finalize(
        DIS_DATA_TYPE_KUOCTET *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUOCTET_finalize_ex(
        DIS_DATA_TYPE_KUOCTET *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUOCTET_copy(
        DIS_DATA_TYPE_KUOCTET *dst,
        const DIS_DATA_TYPE_KUOCTET *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Octet DIS_DATA_TYPE_KCHAR8;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KCHAR8_get_typecode(void); /* Type
                                                                            code
                                                                          */

DDS_SEQUENCE(DIS_DATA_TYPE_KCHAR8Seq, DIS_DATA_TYPE_KCHAR8);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KCHAR8_initialize(DIS_DATA_TYPE_KCHAR8* self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KCHAR8_initialize_ex(
        DIS_DATA_TYPE_KCHAR8 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KCHAR8_finalize(
        DIS_DATA_TYPE_KCHAR8 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KCHAR8_finalize_ex(
        DIS_DATA_TYPE_KCHAR8 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KCHAR8_copy(
        DIS_DATA_TYPE_KCHAR8 *dst,
        const DIS_DATA_TYPE_KCHAR8 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Octet DIS_DATA_TYPE_KUCHAR8;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KUCHAR8_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KUCHAR8Seq, DIS_DATA_TYPE_KUCHAR8);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KUCHAR8_initialize(DIS_DATA_TYPE_KUCHAR8 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUCHAR8_initialize_ex(
        DIS_DATA_TYPE_KUCHAR8 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KUCHAR8_finalize(
        DIS_DATA_TYPE_KUCHAR8 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KUCHAR8_finalize_ex(
        DIS_DATA_TYPE_KUCHAR8 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KUCHAR8_copy(
        DIS_DATA_TYPE_KUCHAR8 *dst,
        const DIS_DATA_TYPE_KUCHAR8 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Float DIS_DATA_TYPE_KFLOAT32;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KFLOAT32_get_typecode(void); /* Type
                                                                              code
                                                                            */

DDS_SEQUENCE(DIS_DATA_TYPE_KFLOAT32Seq, DIS_DATA_TYPE_KFLOAT32);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KFLOAT32_initialize(DIS_DATA_TYPE_KFLOAT32 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KFLOAT32_initialize_ex(
        DIS_DATA_TYPE_KFLOAT32 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KFLOAT32_finalize(
        DIS_DATA_TYPE_KFLOAT32 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KFLOAT32_finalize_ex(
        DIS_DATA_TYPE_KFLOAT32 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KFLOAT32_copy(
        DIS_DATA_TYPE_KFLOAT32 *dst,
        const DIS_DATA_TYPE_KFLOAT32 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Double DIS_DATA_TYPE_KFLOAT64;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KFLOAT64_get_typecode(void); /* Type
                                                                              code
                                                                            */

DDS_SEQUENCE(DIS_DATA_TYPE_KFLOAT64Seq, DIS_DATA_TYPE_KFLOAT64);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KFLOAT64_initialize(DIS_DATA_TYPE_KFLOAT64 *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KFLOAT64_initialize_ex(
        DIS_DATA_TYPE_KFLOAT64 *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KFLOAT64_finalize(
        DIS_DATA_TYPE_KFLOAT64 *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KFLOAT64_finalize_ex(
        DIS_DATA_TYPE_KFLOAT64 *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KFLOAT64_copy(
        DIS_DATA_TYPE_KFLOAT64 *dst,
        const DIS_DATA_TYPE_KFLOAT64 *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef char* DIS_DATA_TYPE_KString;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KString_get_typecode(void); /* Type
                                                                             code
                                                                           */

DDS_SEQUENCE(DIS_DATA_TYPE_KStringSeq, DIS_DATA_TYPE_KString);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KString_initialize(DIS_DATA_TYPE_KString *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KString_initialize_ex(
        DIS_DATA_TYPE_KString *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KString_finalize(
        DIS_DATA_TYPE_KString *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KString_finalize_ex(
        DIS_DATA_TYPE_KString *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KString_copy(
        DIS_DATA_TYPE_KString *dst,
        const DIS_DATA_TYPE_KString *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Boolean DIS_DATA_TYPE_KBOOL;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_KBOOL_get_typecode(void); /* Type
                                                                           code
                                                                         */

DDS_SEQUENCE(DIS_DATA_TYPE_KBOOLSeq, DIS_DATA_TYPE_KBOOL);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_KBOOL_initialize(DIS_DATA_TYPE_KBOOL *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KBOOL_initialize_ex(
        DIS_DATA_TYPE_KBOOL *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_KBOOL_finalize(DIS_DATA_TYPE_KBOOL *self);

NDDSUSERDllExport void DIS_DATA_TYPE_KBOOL_finalize_ex(
        DIS_DATA_TYPE_KBOOL *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_KBOOL_copy(
        DIS_DATA_TYPE_KBOOL *dst,
        const DIS_DATA_TYPE_KBOOL *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DDS_Long DIS_DATA_TYPE_TimeStamp;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_TimeStamp_get_typecode(
        void); /* Type code */

DDS_SEQUENCE(DIS_DATA_TYPE_TimeStampSeq, DIS_DATA_TYPE_TimeStamp);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_TimeStamp_initialize(DIS_DATA_TYPE_TimeStamp *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_TimeStamp_initialize_ex(
        DIS_DATA_TYPE_TimeStamp *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_TimeStamp_finalize(
        DIS_DATA_TYPE_TimeStamp *self);

NDDSUSERDllExport void DIS_DATA_TYPE_TimeStamp_finalize_ex(
        DIS_DATA_TYPE_TimeStamp *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_TimeStamp_copy(
        DIS_DATA_TYPE_TimeStamp *dst,
        const DIS_DATA_TYPE_TimeStamp *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef enum DIS_DATA_TYPE_PDUType {
    Other_PDU_Type = 0,
    Entity_State_PDU_Type = 1,
    Fire_PDU_Type = 2,
    Detonation_PDU_Type = 3,
    Collision_PDU_Type = 4,
    Service_Request_PDU_Type = 5,
    Resupply_Offer_PDU_Type = 6,
    Resupply_Received_PDU_Type = 7,
    Resupply_Cancel_PDU_Type = 8,
    Repair_Complete_PDU_Type = 9,
    Repair_Response_PDU_Type = 10,
    Create_Entity_PDU_Type = 11,
    Remove_Entity_PDU_Type = 12,
    Start_Resume_PDU_Type = 13,
    Stop_Freeze_PDU_Type = 14,
    Acknowledge_PDU_Type = 15,
    Action_Request_PDU_Type = 16,
    Action_Response_PDU_Type = 17,
    Data_Query_PDU_Type = 18,
    Set_Data_PDU_Type = 19,
    Data_PDU_Type = 20,
    Event_Report_PDU_Type = 21,
    Message_PDU_Type = 22,
    Electromagnetic_Emission_PDU_Type = 23,
    Designator_PDU_Type = 24,
    Transmitter_PDU_Type = 25,
    Signal_PDU_Type = 26,
    Receiver_PDU_Type = 27,
    IFF_ATC_NAVAIDS_PDU_Type = 28,
    UnderwaterAcoustic_PDU_Type = 29,
    SupplementalEmission_EntityState_PDU_Type = 30,
    IntercomSignal_PDU_Type = 31,
    IntercomControl_PDU_Type = 32,
    AggregateState_PDU_Type = 33,
    IsGroupOf_PDU_Type = 34,
    TransferControl_PDU_Type = 35,
    IsPartOf_PDU_Type = 36,
    MinefieldState_PDU_Type = 37,
    MinefieldQuery_PDU_Type = 38,
    MinefieldData_PDU_Type = 39,
    MinefieldResponseNAK_PDU_Type = 40,
    EnvironmentalProcess_PDU_Type = 41,
    GriddedData_PDU_Type = 42,
    PointObjectState_PDU_Type = 43,
    LinearObjectState_PDU_Type = 44,
    ArealObjectState_PDU_Type = 45,
    TSPI_PDU_Type = 46,
    Appearance_PDU_Type = 47,
    ArticulatedParts_PDU_Type = 48,
    LEFire_PDU_Type = 49,
    LEDetonation_PDU_Type = 50,
    CreateEntity_R_PDU_Type = 51,
    RemoveEntity_R_PDU_Type = 52,
    Start_Resume_R_PDU_Type = 53,
    Stop_Freeze_R_PDU_Type = 54,
    Acknowledge_R_PDU_Type = 55,
    ActionRequest_R_PDU_Type = 56,
    ActionResponse_R_PDU_Type = 57,
    DataQuery_R_PDU_Type = 58,
    SetData_R_PDU_Type = 59,
    Data_R_PDU_Type = 60,
    EventReport_R_PDU_Type = 61,
    Comment_R_PDU_Type = 62,
    Record_R_PDU_Type = 63,
    SetRecord_R_PDU_Type = 64,
    RecordQuery_R_PDU_Type = 65,
    Collision_Elastic_PDU_Type = 66,
    EntityStateUpdate_PDU_Type = 67,
    DirectedEnergyFire_PDU_Type = 68,
    EntityDamageStatus_PDU_Type = 69,
    IO_Action_PDU_Type = 70,
    IO_Report_PDU_Type = 71,
    Attribute_PDU_Type = 72,
    Announce_Object_PDU_Type = 129,
    Delete_Object_PDU_Type = 130,
    Describe_Event_PDU_Type = 132,
    Describe_Object_PDU_Type = 133,
    Request_Event_PDU_Type = 134,
    Request_Object_PDU_Type = 135
} DIS_DATA_TYPE_PDUType;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_PDUType_get_typecode(void); /* Type
                                                                             code
                                                                           */


DDS_SEQUENCE(DIS_DATA_TYPE_PDUTypeSeq, DIS_DATA_TYPE_PDUType);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_PDUType_initialize(DIS_DATA_TYPE_PDUType *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_PDUType_initialize_ex(
        DIS_DATA_TYPE_PDUType *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_PDUType_finalize(
        DIS_DATA_TYPE_PDUType *self);

NDDSUSERDllExport void DIS_DATA_TYPE_PDUType_finalize_ex(
        DIS_DATA_TYPE_PDUType *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_PDUType_copy(
        DIS_DATA_TYPE_PDUType *dst,
        const DIS_DATA_TYPE_PDUType *src);


NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_PDUType_getValues(DIS_DATA_TYPE_PDUTypeSeq *values);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef enum DIS_DATA_TYPE_ForceID {
    OtherForceID = 0,
    Friendly = 1,
    Opposing = 2,
    Neutral = 3,
    Friendly2 = 4,
    Opposing2 = 5,
    Neutral2 = 6,
    Friendly3 = 7,
    Opposing3 = 8,
    Neutral3 = 9,
    Friendly4 = 10,
    Opposing4 = 11,
    Neutral4 = 12,
    Friendly5 = 13,
    Opposing5 = 14,
    Neutral5 = 15,
    Friendly6 = 16,
    Opposing6 = 17,
    Neutral6 = 18,
    Friendly7 = 19,
    Opposing7 = 20,
    Neutral7 = 21,
    Friendly8 = 22,
    Opposing8 = 23,
    Neutral8 = 24,
    Friendly9 = 25,
    Opposing9 = 26,
    Neutral9 = 27,
    Friendly10 = 28,
    Opposing10 = 29,
    Neutral10 = 30
} DIS_DATA_TYPE_ForceID;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_ForceID_get_typecode(void); /* Type
                                                                             code
                                                                           */


DDS_SEQUENCE(DIS_DATA_TYPE_ForceIDSeq, DIS_DATA_TYPE_ForceID);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_ForceID_initialize(DIS_DATA_TYPE_ForceID *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_ForceID_initialize_ex(
        DIS_DATA_TYPE_ForceID *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_ForceID_finalize(
        DIS_DATA_TYPE_ForceID *self);

NDDSUSERDllExport void DIS_DATA_TYPE_ForceID_finalize_ex(
        DIS_DATA_TYPE_ForceID *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_ForceID_copy(
        DIS_DATA_TYPE_ForceID *dst,
        const DIS_DATA_TYPE_ForceID *src);


NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_ForceID_getValues(DIS_DATA_TYPE_ForceIDSeq *values);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef enum DIS_DATA_TYPE_AggregateState {
    OtherAggregateState = 0,
    Aggregated = 1,
    Disaggregated = 2,
    FullyDisaggregated = 3,
    PseudoDisaggregated = 4,
    PartiallyDisaggregated = 5
} DIS_DATA_TYPE_AggregateState;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_AggregateState_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_AggregateStateSeq, DIS_DATA_TYPE_AggregateState);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_AggregateState_initialize(DIS_DATA_TYPE_AggregateState *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_AggregateState_initialize_ex(
        DIS_DATA_TYPE_AggregateState *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_AggregateState_finalize(
        DIS_DATA_TYPE_AggregateState *self);

NDDSUSERDllExport void DIS_DATA_TYPE_AggregateState_finalize_ex(
        DIS_DATA_TYPE_AggregateState *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_AggregateState_copy(
        DIS_DATA_TYPE_AggregateState *dst,
        const DIS_DATA_TYPE_AggregateState *src);


NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_AggregateState_getValues(DIS_DATA_TYPE_AggregateStateSeq *values);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef enum DIS_DATA_TYPE_Formation {
    OtherFormation = 0,
    Assembly = 1,
    Vee = 2,
    Wedge = 3,
    Line = 4,
    Column = 5
} DIS_DATA_TYPE_Formation;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_Formation_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_FormationSeq, DIS_DATA_TYPE_Formation);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_Formation_initialize(DIS_DATA_TYPE_Formation *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_Formation_initialize_ex(
        DIS_DATA_TYPE_Formation *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_Formation_finalize(
        DIS_DATA_TYPE_Formation *self);

NDDSUSERDllExport void DIS_DATA_TYPE_Formation_finalize_ex(
        DIS_DATA_TYPE_Formation *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_Formation_copy(
        DIS_DATA_TYPE_Formation *dst,
        const DIS_DATA_TYPE_Formation *src);


NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_Formation_getValues(DIS_DATA_TYPE_FormationSeq *values);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


static const DDS_Long DIS_DATA_TYPE_MAX_PDU_SIZE = 8192;
#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_SimulationIdentifierTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_SimulationIdentifierSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_SimulationIdentifierTypeSupport;
class DIS_DATA_TYPE_SimulationIdentifierDataWriter;
class DIS_DATA_TYPE_SimulationIdentifierDataReader;
    #endif

#endif


class DIS_DATA_TYPE_SimulationIdentifier {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_SimulationIdentifierSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_SimulationIdentifierTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_SimulationIdentifierDataWriter DataWriter;
    typedef DIS_DATA_TYPE_SimulationIdentifierDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT16 m_ui16SiteID;

    DIS_DATA_TYPE_KUINT16 m_ui16ApplicationID;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_SimulationIdentifier_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(
        DIS_DATA_TYPE_SimulationIdentifierSeq,
        DIS_DATA_TYPE_SimulationIdentifier);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_SimulationIdentifier_initialize(
        DIS_DATA_TYPE_SimulationIdentifier *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_SimulationIdentifier_initialize_ex(
        DIS_DATA_TYPE_SimulationIdentifier *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_SimulationIdentifier_finalize(
        DIS_DATA_TYPE_SimulationIdentifier *self);

NDDSUSERDllExport void DIS_DATA_TYPE_SimulationIdentifier_finalize_ex(
        DIS_DATA_TYPE_SimulationIdentifier *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_SimulationIdentifier_copy(
        DIS_DATA_TYPE_SimulationIdentifier *dst,
        const DIS_DATA_TYPE_SimulationIdentifier *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_EntityIdentifierTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_EntityIdentifierSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_EntityIdentifierTypeSupport;
class DIS_DATA_TYPE_EntityIdentifierDataWriter;
class DIS_DATA_TYPE_EntityIdentifierDataReader;
    #endif

#endif


class DIS_DATA_TYPE_EntityIdentifier {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_EntityIdentifierSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_EntityIdentifierTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_EntityIdentifierDataWriter DataWriter;
    typedef DIS_DATA_TYPE_EntityIdentifierDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_SimulationIdentifier m_SimulationIdentifier;

    DIS_DATA_TYPE_KUINT16 m_ui16EntityID;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EntityIdentifier_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_EntityIdentifierSeq, DIS_DATA_TYPE_EntityIdentifier);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_EntityIdentifier_initialize(DIS_DATA_TYPE_EntityIdentifier *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityIdentifier_initialize_ex(
        DIS_DATA_TYPE_EntityIdentifier *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityIdentifier_finalize(
        DIS_DATA_TYPE_EntityIdentifier *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityIdentifier_finalize_ex(
        DIS_DATA_TYPE_EntityIdentifier *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityIdentifier_copy(
        DIS_DATA_TYPE_EntityIdentifier *dst,
        const DIS_DATA_TYPE_EntityIdentifier *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_AggregateIdentifierTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_AggregateIdentifierSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_AggregateIdentifierTypeSupport;
class DIS_DATA_TYPE_AggregateIdentifierDataWriter;
class DIS_DATA_TYPE_AggregateIdentifierDataReader;
    #endif

#endif


class DIS_DATA_TYPE_AggregateIdentifier {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_AggregateIdentifierSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_AggregateIdentifierTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_AggregateIdentifierDataWriter DataWriter;
    typedef DIS_DATA_TYPE_AggregateIdentifierDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_SimulationIdentifier m_SimulationIdentifier;

    DIS_DATA_TYPE_KUINT16 m_ui16AggregateID;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_AggregateIdentifier_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(
        DIS_DATA_TYPE_AggregateIdentifierSeq,
        DIS_DATA_TYPE_AggregateIdentifier);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_AggregateIdentifier_initialize(
        DIS_DATA_TYPE_AggregateIdentifier *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_AggregateIdentifier_initialize_ex(
        DIS_DATA_TYPE_AggregateIdentifier *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_AggregateIdentifier_finalize(
        DIS_DATA_TYPE_AggregateIdentifier *self);

NDDSUSERDllExport void DIS_DATA_TYPE_AggregateIdentifier_finalize_ex(
        DIS_DATA_TYPE_AggregateIdentifier *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_AggregateIdentifier_copy(
        DIS_DATA_TYPE_AggregateIdentifier *dst,
        const DIS_DATA_TYPE_AggregateIdentifier *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_EntityTypeTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_EntityTypeSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_EntityTypeTypeSupport;
class DIS_DATA_TYPE_EntityTypeDataWriter;
class DIS_DATA_TYPE_EntityTypeDataReader;
    #endif

#endif


class DIS_DATA_TYPE_EntityType {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_EntityTypeSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_EntityTypeTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_EntityTypeDataWriter DataWriter;
    typedef DIS_DATA_TYPE_EntityTypeDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_ui8EntityKind;

    DIS_DATA_TYPE_KUINT8 m_ui8Domain;

    DIS_DATA_TYPE_KUINT16 m_ui16Country;

    DIS_DATA_TYPE_KUINT8 m_ui8Category;

    DIS_DATA_TYPE_KUINT8 m_ui8SubCategory;

    DIS_DATA_TYPE_KUINT8 m_ui8Specific;

    DIS_DATA_TYPE_KUINT8 m_ui8Extra;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EntityType_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_EntityTypeSeq, DIS_DATA_TYPE_EntityType);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_EntityType_initialize(DIS_DATA_TYPE_EntityType *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityType_initialize_ex(
        DIS_DATA_TYPE_EntityType *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityType_finalize(
        DIS_DATA_TYPE_EntityType *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityType_finalize_ex(
        DIS_DATA_TYPE_EntityType *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityType_copy(
        DIS_DATA_TYPE_EntityType *dst,
        const DIS_DATA_TYPE_EntityType *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_VectorTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_VectorSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_VectorTypeSupport;
class DIS_DATA_TYPE_VectorDataWriter;
class DIS_DATA_TYPE_VectorDataReader;
    #endif

#endif


class DIS_DATA_TYPE_Vector {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_VectorSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_VectorTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_VectorDataWriter DataWriter;
    typedef DIS_DATA_TYPE_VectorDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KFLOAT32 m_f32X;

    DIS_DATA_TYPE_KFLOAT32 m_f32Y;

    DIS_DATA_TYPE_KFLOAT32 m_f32Z;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_Vector_get_typecode(void); /* Type
                                                                            code
                                                                          */


DDS_SEQUENCE(DIS_DATA_TYPE_VectorSeq, DIS_DATA_TYPE_Vector);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_Vector_initialize(DIS_DATA_TYPE_Vector *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_Vector_initialize_ex(
        DIS_DATA_TYPE_Vector *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_Vector_finalize(
        DIS_DATA_TYPE_Vector *self);

NDDSUSERDllExport void DIS_DATA_TYPE_Vector_finalize_ex(
        DIS_DATA_TYPE_Vector *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_Vector_copy(
        DIS_DATA_TYPE_Vector *dst,
        const DIS_DATA_TYPE_Vector *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_WorldCoordinatesTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_WorldCoordinatesSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_WorldCoordinatesTypeSupport;
class DIS_DATA_TYPE_WorldCoordinatesDataWriter;
class DIS_DATA_TYPE_WorldCoordinatesDataReader;
    #endif

#endif


class DIS_DATA_TYPE_WorldCoordinates {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_WorldCoordinatesSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_WorldCoordinatesTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_WorldCoordinatesDataWriter DataWriter;
    typedef DIS_DATA_TYPE_WorldCoordinatesDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KFLOAT64 m_f64X;

    DIS_DATA_TYPE_KFLOAT64 m_f64Y;

    DIS_DATA_TYPE_KFLOAT64 m_f64Z;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_WorldCoordinates_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_WorldCoordinatesSeq, DIS_DATA_TYPE_WorldCoordinates);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_WorldCoordinates_initialize(DIS_DATA_TYPE_WorldCoordinates *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_WorldCoordinates_initialize_ex(
        DIS_DATA_TYPE_WorldCoordinates *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_WorldCoordinates_finalize(
        DIS_DATA_TYPE_WorldCoordinates *self);

NDDSUSERDllExport void DIS_DATA_TYPE_WorldCoordinates_finalize_ex(
        DIS_DATA_TYPE_WorldCoordinates *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_WorldCoordinates_copy(
        DIS_DATA_TYPE_WorldCoordinates *dst,
        const DIS_DATA_TYPE_WorldCoordinates *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_EulerAnglesTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_EulerAnglesSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_EulerAnglesTypeSupport;
class DIS_DATA_TYPE_EulerAnglesDataWriter;
class DIS_DATA_TYPE_EulerAnglesDataReader;
    #endif

#endif


class DIS_DATA_TYPE_EulerAngles {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_EulerAnglesSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_EulerAnglesTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_EulerAnglesDataWriter DataWriter;
    typedef DIS_DATA_TYPE_EulerAnglesDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KFLOAT32 m_f32Psi;

    DIS_DATA_TYPE_KFLOAT32 m_f32Theta;

    DIS_DATA_TYPE_KFLOAT32 m_f32Phi;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EulerAngles_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_EulerAnglesSeq, DIS_DATA_TYPE_EulerAngles);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_EulerAngles_initialize(DIS_DATA_TYPE_EulerAngles *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EulerAngles_initialize_ex(
        DIS_DATA_TYPE_EulerAngles *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EulerAngles_finalize(
        DIS_DATA_TYPE_EulerAngles *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EulerAngles_finalize_ex(
        DIS_DATA_TYPE_EulerAngles *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EulerAngles_copy(
        DIS_DATA_TYPE_EulerAngles *dst,
        const DIS_DATA_TYPE_EulerAngles *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_ArticulationParametersTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_ArticulationParametersSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_ArticulationParametersTypeSupport;
class DIS_DATA_TYPE_ArticulationParametersDataWriter;
class DIS_DATA_TYPE_ArticulationParametersDataReader;
    #endif

#endif


class DIS_DATA_TYPE_ArticulationParameters {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_ArticulationParametersSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_ArticulationParametersTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_ArticulationParametersDataWriter DataWriter;
    typedef DIS_DATA_TYPE_ArticulationParametersDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_ui8ArticulationType;

    DIS_DATA_TYPE_KUINT8 m_ui8ParmeterChange;

    DIS_DATA_TYPE_KUINT16 m_ui16AttachementID;

    DIS_DATA_TYPE_KUINT32 m_ui32ParamTypeVariantUnion;

    DIS_DATA_TYPE_KUINT64 m_ui64ParamValue;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode*
DIS_DATA_TYPE_ArticulationParameters_get_typecode(void); /* Type code */


DDS_SEQUENCE(
        DIS_DATA_TYPE_ArticulationParametersSeq,
        DIS_DATA_TYPE_ArticulationParameters);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_ArticulationParameters_initialize(
        DIS_DATA_TYPE_ArticulationParameters *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_ArticulationParameters_initialize_ex(
        DIS_DATA_TYPE_ArticulationParameters *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_ArticulationParameters_finalize(
        DIS_DATA_TYPE_ArticulationParameters *self);

NDDSUSERDllExport void DIS_DATA_TYPE_ArticulationParameters_finalize_ex(
        DIS_DATA_TYPE_ArticulationParameters *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_ArticulationParameters_copy(
        DIS_DATA_TYPE_ArticulationParameters *dst,
        const DIS_DATA_TYPE_ArticulationParameters *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


typedef DIS_DATA_TYPE_KUINT32 DIS_DATA_TYPE_EntityAppearance;


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EntityAppearance_get_typecode(
        void); /* Type code */

DDS_SEQUENCE(DIS_DATA_TYPE_EntityAppearanceSeq, DIS_DATA_TYPE_EntityAppearance);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_EntityAppearance_initialize(DIS_DATA_TYPE_EntityAppearance *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityAppearance_initialize_ex(
        DIS_DATA_TYPE_EntityAppearance *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityAppearance_finalize(
        DIS_DATA_TYPE_EntityAppearance *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityAppearance_finalize_ex(
        DIS_DATA_TYPE_EntityAppearance *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityAppearance_copy(
        DIS_DATA_TYPE_EntityAppearance *dst,
        const DIS_DATA_TYPE_EntityAppearance *src);


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_DeadReckoningParameterTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_DeadReckoningParameterSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_DeadReckoningParameterTypeSupport;
class DIS_DATA_TYPE_DeadReckoningParameterDataWriter;
class DIS_DATA_TYPE_DeadReckoningParameterDataReader;
    #endif

#endif


class DIS_DATA_TYPE_DeadReckoningParameter {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_DeadReckoningParameterSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_DeadReckoningParameterTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_DeadReckoningParameterDataWriter DataWriter;
    typedef DIS_DATA_TYPE_DeadReckoningParameterDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_ui8DeadRecknoningAlgorithm;

    DIS_DATA_TYPE_KOCTET m_OtherParams[15];

    DIS_DATA_TYPE_Vector m_LinearAcceleration;

    DIS_DATA_TYPE_Vector m_AngularVelocity;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode*
DIS_DATA_TYPE_DeadReckoningParameter_get_typecode(void); /* Type code */


DDS_SEQUENCE(
        DIS_DATA_TYPE_DeadReckoningParameterSeq,
        DIS_DATA_TYPE_DeadReckoningParameter);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_DeadReckoningParameter_initialize(
        DIS_DATA_TYPE_DeadReckoningParameter *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_DeadReckoningParameter_initialize_ex(
        DIS_DATA_TYPE_DeadReckoningParameter *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_DeadReckoningParameter_finalize(
        DIS_DATA_TYPE_DeadReckoningParameter *self);

NDDSUSERDllExport void DIS_DATA_TYPE_DeadReckoningParameter_finalize_ex(
        DIS_DATA_TYPE_DeadReckoningParameter *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_DeadReckoningParameter_copy(
        DIS_DATA_TYPE_DeadReckoningParameter *dst,
        const DIS_DATA_TYPE_DeadReckoningParameter *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_EntityMarkingTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_EntityMarkingSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_EntityMarkingTypeSupport;
class DIS_DATA_TYPE_EntityMarkingDataWriter;
class DIS_DATA_TYPE_EntityMarkingDataReader;
    #endif

#endif


class DIS_DATA_TYPE_EntityMarking {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_EntityMarkingSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_EntityMarkingTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_EntityMarkingDataWriter DataWriter;
    typedef DIS_DATA_TYPE_EntityMarkingDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_ui8EntityMarkingCharacterSet;

    DIS_DATA_TYPE_KCHAR8 m_sEntityMarkingString[12];
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EntityMarking_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(DIS_DATA_TYPE_EntityMarkingSeq, DIS_DATA_TYPE_EntityMarking);

NDDSUSERDllExport RTIBool
DIS_DATA_TYPE_EntityMarking_initialize(DIS_DATA_TYPE_EntityMarking *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityMarking_initialize_ex(
        DIS_DATA_TYPE_EntityMarking *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityMarking_finalize(
        DIS_DATA_TYPE_EntityMarking *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityMarking_finalize_ex(
        DIS_DATA_TYPE_EntityMarking *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityMarking_copy(
        DIS_DATA_TYPE_EntityMarking *dst,
        const DIS_DATA_TYPE_EntityMarking *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif


extern const char *DIS_DATA_TYPE_EntityCapabilitiesTYPENAME;


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct DIS_DATA_TYPE_EntityCapabilitiesSeq;

    #ifndef NDDS_STANDALONE_TYPE
class DIS_DATA_TYPE_EntityCapabilitiesTypeSupport;
class DIS_DATA_TYPE_EntityCapabilitiesDataWriter;
class DIS_DATA_TYPE_EntityCapabilitiesDataReader;
    #endif

#endif


class DIS_DATA_TYPE_EntityCapabilities {
public:
#ifdef __cplusplus
    typedef struct DIS_DATA_TYPE_EntityCapabilitiesSeq Seq;

    #ifndef NDDS_STANDALONE_TYPE
    typedef DIS_DATA_TYPE_EntityCapabilitiesTypeSupport TypeSupport;
    typedef DIS_DATA_TYPE_EntityCapabilitiesDataWriter DataWriter;
    typedef DIS_DATA_TYPE_EntityCapabilitiesDataReader DataReader;
    #endif

#endif

    DIS_DATA_TYPE_KUINT8 m_AmmoFuelRecoveryRepair;

    DIS_DATA_TYPE_KUINT8 m_Unused1;

    DIS_DATA_TYPE_KUINT8 m_Unused2;

    DIS_DATA_TYPE_KUINT8 m_Unused3;
};


#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
#endif


NDDSUSERDllExport DDS_TypeCode *DIS_DATA_TYPE_EntityCapabilities_get_typecode(
        void); /* Type code */


DDS_SEQUENCE(
        DIS_DATA_TYPE_EntityCapabilitiesSeq,
        DIS_DATA_TYPE_EntityCapabilities);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityCapabilities_initialize(
        DIS_DATA_TYPE_EntityCapabilities *self);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityCapabilities_initialize_ex(
        DIS_DATA_TYPE_EntityCapabilities *self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityCapabilities_finalize(
        DIS_DATA_TYPE_EntityCapabilities *self);

NDDSUSERDllExport void DIS_DATA_TYPE_EntityCapabilities_finalize_ex(
        DIS_DATA_TYPE_EntityCapabilities *self,
        RTIBool deletePointers);

NDDSUSERDllExport RTIBool DIS_DATA_TYPE_EntityCapabilities_copy(
        DIS_DATA_TYPE_EntityCapabilities *dst,
        const DIS_DATA_TYPE_EntityCapabilities *src);

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
     */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
#endif


#endif /* DIS_Data_Type_526845752_h */
