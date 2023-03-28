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

  DisParser.c

  =========================================================================*/

#include "ndds/ndds_c.h"
#include "dds_c/dds_c_dynamicdata.h"
#include "routingservice/routingservice_adapter.h"

#include "DisParser.h"
#include "DisSerializer.h"
#include "DIS_Data_Type.h"

#ifdef RTI_WIN32
    /* strtok warnings */
    #pragma warning(disable : 4996)
#endif


/*****************************************************************************

  Public Functions

 *****************************************************************************/


RTIBool DisParser_ParseMessage(
        struct DDS_DynamicData* sampleOut,
        const DIS_PDU_Header* pHeader,
        char* pInputStream,
        DDS_Long* bytesRead)
{
    RTIBool success = RTI_FALSE;

    switch (pHeader->m_ui8PDUType) {
    /* Messages routed from DIS to DDS */
    case Entity_State_PDU_Type:
    case Fire_PDU_Type:
    case Detonation_PDU_Type:
    case Collision_PDU_Type:
    case Create_Entity_PDU_Type:
    case Remove_Entity_PDU_Type:
    case Start_Resume_PDU_Type:
    case Stop_Freeze_PDU_Type:
    case Acknowledge_PDU_Type:
    case Action_Request_PDU_Type:
    case Action_Response_PDU_Type:
    case Data_Query_PDU_Type:
    case Set_Data_PDU_Type:
    case Data_PDU_Type:
    case Event_Report_PDU_Type:
    case Message_PDU_Type:
    case Designator_PDU_Type:
    case Transmitter_PDU_Type:
    case Signal_PDU_Type:
    case Receiver_PDU_Type:
    case IntercomSignal_PDU_Type:
    case IntercomControl_PDU_Type:
    case AggregateState_PDU_Type:
    case IsGroupOf_PDU_Type:
    case TransferControl_PDU_Type:
    case IsPartOf_PDU_Type:
    case EnvironmentalProcess_PDU_Type:
    case GriddedData_PDU_Type:
    case PointObjectState_PDU_Type:
    case LinearObjectState_PDU_Type:
    case ArealObjectState_PDU_Type:
    case TSPI_PDU_Type:
    case LEFire_PDU_Type:
    case LEDetonation_PDU_Type:
    case CreateEntity_R_PDU_Type:
    case RemoveEntity_R_PDU_Type:
    case Start_Resume_R_PDU_Type:
    case Stop_Freeze_R_PDU_Type:
    case Acknowledge_R_PDU_Type:
    case ActionRequest_R_PDU_Type:
    case ActionResponse_R_PDU_Type:
    case DataQuery_R_PDU_Type:
    case SetData_R_PDU_Type:
    case Data_R_PDU_Type:
    case EventReport_R_PDU_Type:
    case Comment_R_PDU_Type:
    case Record_R_PDU_Type:
    case SetRecord_R_PDU_Type:
    case RecordQuery_R_PDU_Type:
    case Collision_Elastic_PDU_Type:
    case EntityStateUpdate_PDU_Type:
    case DirectedEnergyFire_PDU_Type:
    case EntityDamageStatus_PDU_Type:
        success = DisSerializer_deserializeSample(
                sampleOut,
                pInputStream,
                bytesRead);
        break;

    case Other_PDU_Type:
    case Service_Request_PDU_Type:
    case Resupply_Offer_PDU_Type:
    case Resupply_Received_PDU_Type:
    case Resupply_Cancel_PDU_Type:
    case Repair_Complete_PDU_Type:
    case Repair_Response_PDU_Type:
    case Electromagnetic_Emission_PDU_Type:
    case IFF_ATC_NAVAIDS_PDU_Type:
    case UnderwaterAcoustic_PDU_Type:
    case SupplementalEmission_EntityState_PDU_Type:
    case MinefieldState_PDU_Type:
    case MinefieldQuery_PDU_Type:
    case MinefieldData_PDU_Type:
    case MinefieldResponseNAK_PDU_Type:
    case Appearance_PDU_Type:
    case ArticulatedParts_PDU_Type:
    case IO_Action_PDU_Type:
    case IO_Report_PDU_Type:
    case Attribute_PDU_Type:
    case Announce_Object_PDU_Type:
    case Delete_Object_PDU_Type:
    case Describe_Event_PDU_Type:
    case Describe_Object_PDU_Type:
    case Request_Event_PDU_Type:
    case Request_Object_PDU_Type:
        fprintf(stderr, "PDU type %d not implemented\n", pHeader->m_ui8PDUType);
        break;

    default:
        fprintf(stderr, "Attempted to parse unknown msgType: %d\n",
               pHeader->m_ui8PDUType);
        break;
    }
    return success;
}

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
        struct DDS_DynamicData* sample,
        RTI_INT32 msgType,
        RTI_UINT32 msgInstance,
        RTI_INT8* stream,
        RTI_INT32 maxLen,
        RTI_RoutingServiceEnvironment* env)
{
    RTI_INT32 bytesSerialized = 0;
    RTI_INT32 payloadLength = 0;

    /* DDS to DIS Route */

#ifdef ENABLE_DIS_DEBUG_MSGS
    if (RTI_RoutingServiceEnvironment_get_verbosity(env)
        >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
        printf("Serializing PDU: %d\n", msgType);
#endif

    switch (msgType) {
    /* Messages routed from DDS to DIS */
    case Other_PDU_Type:
    case Entity_State_PDU_Type:
    case Fire_PDU_Type:
    case Detonation_PDU_Type:
    case Collision_PDU_Type:
    case Service_Request_PDU_Type:
    case Resupply_Offer_PDU_Type:
    case Resupply_Received_PDU_Type:
    case Resupply_Cancel_PDU_Type:
    case Repair_Complete_PDU_Type:
    case Repair_Response_PDU_Type:
    case Create_Entity_PDU_Type:
    case Remove_Entity_PDU_Type:
    case Start_Resume_PDU_Type:
    case Stop_Freeze_PDU_Type:
    case Acknowledge_PDU_Type:
    case Action_Request_PDU_Type:
    case Action_Response_PDU_Type:
    case Data_Query_PDU_Type:
    case Set_Data_PDU_Type:
    case Data_PDU_Type:
    case Event_Report_PDU_Type:
    case Message_PDU_Type:
    case Electromagnetic_Emission_PDU_Type:
    case Designator_PDU_Type:
    case Transmitter_PDU_Type:
    case Signal_PDU_Type:
    case Receiver_PDU_Type:
    case IFF_ATC_NAVAIDS_PDU_Type:
    case UnderwaterAcoustic_PDU_Type:
    case SupplementalEmission_EntityState_PDU_Type:
    case IntercomSignal_PDU_Type:
    case IntercomControl_PDU_Type:
    case AggregateState_PDU_Type:
    case IsGroupOf_PDU_Type:
    case TransferControl_PDU_Type:
    case IsPartOf_PDU_Type:
    case MinefieldState_PDU_Type:
    case MinefieldQuery_PDU_Type:
    case MinefieldData_PDU_Type:
    case MinefieldResponseNAK_PDU_Type:
    case EnvironmentalProcess_PDU_Type:
    case GriddedData_PDU_Type:
    case PointObjectState_PDU_Type:
    case LinearObjectState_PDU_Type:
    case ArealObjectState_PDU_Type:
    case TSPI_PDU_Type:
    case Appearance_PDU_Type:
    case ArticulatedParts_PDU_Type:
    case LEFire_PDU_Type:
    case LEDetonation_PDU_Type:
    case CreateEntity_R_PDU_Type:
    case RemoveEntity_R_PDU_Type:
    case Start_Resume_R_PDU_Type:
    case Stop_Freeze_R_PDU_Type:
    case Acknowledge_R_PDU_Type:
    case ActionRequest_R_PDU_Type:
    case ActionResponse_R_PDU_Type:
    case DataQuery_R_PDU_Type:
    case SetData_R_PDU_Type:
    case Data_R_PDU_Type:
    case EventReport_R_PDU_Type:
    case Comment_R_PDU_Type:
    case Record_R_PDU_Type:
    case SetRecord_R_PDU_Type:
    case RecordQuery_R_PDU_Type:
    case Collision_Elastic_PDU_Type:
    case EntityStateUpdate_PDU_Type:
    case DirectedEnergyFire_PDU_Type:
    case EntityDamageStatus_PDU_Type:
    case IO_Action_PDU_Type:
    case IO_Report_PDU_Type:
    case Attribute_PDU_Type:
    case Announce_Object_PDU_Type:
    case Delete_Object_PDU_Type:
    case Describe_Event_PDU_Type:
    case Describe_Object_PDU_Type:
    case Request_Event_PDU_Type:
    case Request_Object_PDU_Type:
#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("Serializing payload for msgType: %d.\n", msgType);
#endif
        payloadLength = DisSerializer_serializeSample(
                sample,
                (DDS_Char*) &stream[0],
                maxLen,
                env);
        break;
    default:
        fprintf(stderr,
                "Attempted to serialize payload for unknown msgType: %d\n",
                msgType);
        break;
    }

    if (payloadLength > 0) {
#ifdef ENABLE_DIS_DEBUG_MSGS
        if (RTI_RoutingServiceEnvironment_get_verbosity(env)
            >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("DIS payload bytes serialized: %d\n", payloadLength);
#endif
        bytesSerialized = payloadLength;
    }

#ifdef ENABLE_DIS_DEBUG_MSGS
    if (RTI_RoutingServiceEnvironment_get_verbosity(env)
        >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
        printf("DIS total bytes serialized: %d\n", bytesSerialized);
#endif
    return bytesSerialized;
}
