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

/*=========================================================================
  RTI Routing Service DIS Socket Adapter
  =========================================================================

  DisParser.h

  =========================================================================*/

#ifndef DisParser_h
#define DisParser_h

#include <ndds/ndds_c.h>
#include <dds_c/dds_c_dynamicdata.h>
#include <routingservice/routingservice_adapter.h>

#include "HeaderPDU.h"
/* #include <memory> */

/* #pragma pack(2) */

/**
 *
 * @brief Deserializes from the provided stream and populates a dynamic data
 *        sample.
 *
 * @param sampleOut The sample whose field values shall be set
 * @param pHeader The DIS Header for the sample
 * @param pInputStream The stream to be deserialized
 * @param bytesRead The number of bytes to be read.
 *
 * @return 0 if error, otherwise 1
 *
 */
RTI_INT32 DisParser_ParseMessage(
        struct DDS_DynamicData *sampleOut,
        const DIS_PDU_Header *pHeader,
        char *pInputStream,
        DDS_Long *bytesRead);

/**
 *
 * @brief Serializes a dynamic data sample into the provided stream.
 *
 * @param sample The data sample to be serialized
 * @param msgType The DIS message type for the sample
 * @param msgInstance The DIS message instance for the sample
 * @param stream The stream to serialized the sample into
 * @param maxLen The maximum length of the stream
 * @param env The environment to report error messages
 *
 * @return 0 if error, otherwise number of bytes serialized
 *
 */
RTI_INT32 DisParser_SerializeSample(
        struct DDS_DynamicData *sample,
        RTI_INT32 msgType,
        RTI_UINT32 msgInstance,
        RTI_INT8 *stream,
        RTI_INT32 maxLen,
        RTI_RoutingServiceEnvironment *env);

#endif /* DisParser_h */
