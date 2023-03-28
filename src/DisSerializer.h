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
/* Serialization.h                                                           */
/*                                                                           */
/* ========================================================================= */

#ifndef DisSerializer_h
#define DisSerializer_h

#if defined(RTI_UNIX) && !defined(RTI_LINUX) && !defined(RTI_IRIX) \
        && !defined(RTI_ENDIAN_LITTLE)
    #define RTI_CDR_SIZEOF_LONG_DOUBLE 16
#endif

#include <ndds/ndds_c.h>
#include <dds_c/dds_c_infrastructure.h>
#include <dds_c/dds_c_dynamicdata.h>

/**
 *
 * @brief Serialize a sample into the provided stream.
 *
 * @param sample The data sample to be serialized
 * @param stream The stream to serialize into
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
        RTI_RoutingServiceEnvironment *env);

/**
 *
 * @brief Deserialize from the stream into the provided sample.
 *
 * @param sample The data sample to serialize into
 * @param stream The stream to be deserialized
 * @param bytesRead The number of bytes to read
 *
 * @return 0 if error, otherwise number of bytes serialized
 *
 */
RTIBool DisSerializer_deserializeSample(
        DDS_DynamicData *sample,
        DDS_Char *stream,
        DDS_Long *bytesRead);

#endif /* DisSerializer_h */
