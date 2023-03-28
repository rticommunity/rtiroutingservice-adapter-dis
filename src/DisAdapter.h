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

/* ======================================================================== */
/* RTI Routing Service STANAG 4586 Socket Adapter                           */
/* ======================================================================== */
/*                                                                          */
/* Disadapter.h                                                      */
/*                                                                          */
/* ======================================================================== */


#ifndef DisAdapter_h
#define DisAdapter_h

#include "routingservice/routingservice_adapter.h"

#ifdef DllExport
    #undef DllExport
#endif
#ifdef RTI_WIN32
    #define DllExport extern "C" __declspec(dllexport)
#else
    #define DllExport extern "C"
#endif


/**
 *
 * @brief Entry point to the adapter plugin.
 *
 * @param
 *
 * @return
 *
 */
DllExport struct RTI_RoutingServiceAdapterPlugin *DisAdapterPlugin_create(
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env);


/**
 *
 * @brief This function creates an adapter connection.  Each adapter connection
 *        will have associated a receive thread that will read data from an UDP
 *        socket.
 *
 * @param
 *
 * @return
 *
 */
DllExport void DisAdapterPlugin_delete(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        RTI_RoutingServiceEnvironment *env);


/**
 * @brief This function creates an adapter connection.  Each adapter connection
 *        will have associated a receive thread that will read data from an UDP
 *        socket.
 *
 * @param
 *
 * @return
 *
 */
DllExport RTI_RoutingServiceConnection DisAdapterPlugin_create_connection(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        const char *routing_service_name,
        const char *routing_service_group_name,
        const struct RTI_RoutingServiceStreamReaderListener*
                input_disc_listener,
        const struct RTI_RoutingServiceStreamReaderListener*
                output_disc_listener,
        const struct RTI_RoutingServiceTypeInfo **registeredTypes,
        int registeredTypeCount,
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env);

DllExport void DisAdapterPlugin_delete_connection(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceEnvironment *env);


DllExport RTI_RoutingServiceStreamReader
DisAdapterConnection_create_stream_reader(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceSession session,
        const struct RTI_RoutingServiceStreamInfo *stream_info,
        const struct RTI_RoutingServiceProperties *properties,
        const struct RTI_RoutingServiceStreamReaderListener *listener,
        RTI_RoutingServiceEnvironment *env);


/**
 *
 * @brief The connection thread reads messages from a socket and associates them
 *        with a StreamReader based on the streamName (topicName).
 *
 * @param threadParam
 *
 */
DllExport void DisAdapterConnection_delete_stream_reader(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceEnvironment *env);


/**
 *
 * @brief This function will be called by RTI Routing Service after being
 *        notified that new data is available. Although the signature of the
 *        function allows returning more than one sample, for the sake of
 *        simplicity, the implementation only returns one sample each time the
 *        function is called.
 *
 * @param stream_reader
 * @param sample_list
 * @param info_list
 * @param count
 * @param env
 *
 */
DllExport void DisAdapterStreamReader_read(
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceSample **sample_list,
        RTI_RoutingServiceSampleInfo **info_list,
        int *count,
        RTI_RoutingServiceEnvironment *env);


/**
 *
 * @brief The loan on the samples provided by DisAdapterStreamReader_read()
 *        is returned to the adapter using this function.
 *
 * @param stream_reader
 * @param sample_list
 * @param info_list
 * @param count
 * @param env
 *
 */
DllExport void DisAdapterStreamReader_return_loan(
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceSample *sample_list,
        RTI_RoutingServiceSampleInfo *info_list,
        int count,
        RTI_RoutingServiceEnvironment *env);


DllExport RTI_RoutingServiceStreamWriter
DisAdapterConnection_create_stream_writer(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceSession session,
        const struct RTI_RoutingServiceStreamInfo *stream_info,
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env);


DllExport void DisAdapterConnection_delete_stream_writer(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceStreamWriter stream_writer,
        RTI_RoutingServiceEnvironment *env);


/**
 * This operation is not taking any mutex to protect the write operation.
 * Therefore all routes must be in a single session.
 * A mutex could be added mutex in the connection to protect the write operation.

 * @param stream_writer
 * @param sample_list
 * @param info_list
 * @param count
 * @param env
 *
 * @return
 *
 */
DllExport int DisAdapterStreamWriter_write(
        RTI_RoutingServiceStreamWriter stream_writer,
        const RTI_RoutingServiceSample *sample_list,
        const RTI_RoutingServiceSampleInfo *info_list,
        int count,
        RTI_RoutingServiceEnvironment *env);

#endif /* DisAdapter_h */
