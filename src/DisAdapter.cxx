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
/* RTI Routing Service DIS Socket Adapter                                    */
/* ========================================================================= */
/*                                                                           */
/* SocketAdapter.c                                                           */
/*                                                                           */
/* Conversion between byte stream and DDS dynamic data samples               */
/*                                                                           */
/* This a pluggable adapter that reads bytes from a socket                   */
/* providing them to Routing Service as DynamicData samples                  */
/* and receives samples from Routing Service to write them in a socket       */
/*                                                                           */
/* ========================================================================= */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <ndds/ndds_c.h>

#include "SocketUtil.h"
#include "DisAdapter.h"
#include "DisParser.h"

#ifdef RTI_WIN32
    #include <Winsock2.h>
    #include <process.h>
    /* strtok warnings */
    #pragma warning(disable : 4996)
#else
    #include <sys/select.h>
    #include <semaphore.h>
    #include <pthread.h>
#endif

#define ENABLE_DIS_DEBUG_MSGS

#define SOCKET_ADAPTER_UNBLOCK_MESSAGE "SocketAdapter:unblock"
#define SOCKET_ADAPTER_UNBLOCK_MESSAGE_SIZE \
    (strlen(SOCKET_ADAPTER_UNBLOCK_MESSAGE) + 1)

/* ========================================================================= */
/*                                                                           */
/* Data types                                                                */
/*                                                                           */
/* ========================================================================= */
extern "C" struct DisAdapterPlugin {
    struct RTI_RoutingServiceAdapterPlugin base;
};

RTI_RoutingServiceVerbosity _verbosity;


/*****************************************************************************/

struct DisAdapterConnection {
    struct DisAdapterPlugin *adapter;
    /* is connection enabled */
    RTIBool enabled;
    /* hostId for local processing node*/
    RTI_INT32 hostId;
    /* port number to bind socket for receiving data */
    unsigned short receivePort;
    /* the socket the connection thread will read data from */
    int readSocket;
    /* the socket that will be used to write data */
    int writeSocket;
    /* Destination address where the StreamWriters will send data */
    struct sockaddr_in sendAddr;
    /* is receive thread created (one per connection) */
    RTIBool threadCreated;
    /* the receive thread */
#ifdef RTI_WIN32
    HANDLE thread;
#else
    pthread_t thread;
#endif
    /* max msg size, specified in router properties */
    int maxMessageSize;
    /* Buffer to hold received data */
    char *recvBuffer;
    /* Buffer to hold data to send */
    char *sendBuffer;
    /* StreamReader list */
    struct DisAdapterStreamReader *firstStreamReader;
    /* number of StreamReaders created */
    int streamReaderCount;
    /* StreamWriter list */
    struct DisAdapterStreamWriter *firstStreamWriter;
    /* number of StreamWriters created */
    int streamWriterCount;
    /* verbosity */
    RTI_RoutingServiceVerbosity verbosity;
};

/*
 * This implementation of the StreamReader only caches one sample
 */
struct DisDynamicDataList {
    struct DisDynamicDataList *next;
    struct DDS_DynamicData *dynData;
    bool inUse;

    /* Including a dummy SampleInfo - its valid flag is always true -
     * to keep the RS processor that will accompany this Adapter happy.
     * It poses no issue if the RS processor is not available since
     * all samples originating from the adapter will be valid; i.e.
     * never disposed or unregistered. */
    struct DDS_SampleInfo *sampleInfo;
};

struct DisAdapterStreamReader {
    struct DisAdapterStreamReader *next;
    struct DisAdapterStreamReader *prev;
    struct RTI_RoutingServiceStreamReaderListener listener;
    /* streamName (topic Name) */
    char *streamName;
    /* DIS msgType (message wrapper) */
    int msgType;
    /* buffering for a single data sample */
    /* struct DDS_DynamicData *dynData; */
    struct DisDynamicDataList *dynDataList;
    struct DDS_TypeCode *tc;
    /* is semaphore initialized */
    RTIBool dynDataSemInit;
    /* semaphore to protect access to data storage */
    struct RTIOsapiSemaphore *dynDataSem;
};

struct DisAdapterStreamWriter {
    struct DisAdapterStreamWriter *next;
    struct DisAdapterStreamWriter *prev;
    struct DisAdapterConnection *cx;
    /* streamName (topic Name) */
    char *streamName;
    /* DIS msgType (message wrapper) */
    int msgType;
    /* DIS msgInstance (message wrapper) */
    unsigned int msgInstance;
};

void swapLong(unsigned long* addr)
{
    unsigned char temp[4];
    unsigned char *pAddr = (unsigned char*) addr;
    temp[0] = pAddr[3];
    temp[1] = pAddr[2];
    temp[2] = pAddr[1];
    temp[3] = pAddr[0];
    memcpy(addr, &temp[0], sizeof(unsigned long));
}


/*=========================================================================

 Private function prototypes

 =========================================================================*/

static void* DisAdapterConnection_run(void *threadParam);

static int DisAdapterConnection_unblock(struct DisAdapterConnection *self);


/*=========================================================================

   Stream reader methods
   In this simple implementation each StreamReader will be able to cache only
   one sample

 =========================================================================*/

void DisAdapterStreamReader_read(
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceSample **sample_list,
        RTI_RoutingServiceSampleInfo **info_list,
        int *count,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterStreamReader *self =
            (struct DisAdapterStreamReader*) stream_reader;
    *count = 1;
    *sample_list = (void**) &self->dynDataList->dynData;
    *info_list = (void**) &self->dynDataList->sampleInfo;
}


void DisAdapterStreamReader_return_loan(
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceSample *sample_list,
        RTI_RoutingServiceSampleInfo *info_list,
        int count,
        RTI_RoutingServiceEnvironment *env)
{
    int error;
    struct DisAdapterStreamReader *self =
            (struct DisAdapterStreamReader*) stream_reader;

    /* find which sample was processed & set inUse false */
    DisDynamicDataList *pList = self->dynDataList;

    for (int i = 0; i < count; i++) {
        pList = self->dynDataList;
        while (pList != NULL) {
            if (pList->dynData == sample_list[i]) {
                pList->inUse = RTI_FALSE;
            }
            pList = pList->next;
        }
    }

    if (RTIOsapiSemaphore_give(self->dynDataSem)
        != RTI_OSAPI_SEMAPHORE_STATUS_OK) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error giving StreamReader semaphore");
    }
}

/*=========================================================================

    Stream writer methods

 =========================================================================*/

int DisAdapterStreamWriter_write(
        RTI_RoutingServiceStreamWriter stream_writer,
        const RTI_RoutingServiceSample *sample_list,
        const RTI_RoutingServiceSampleInfo *info_list,
        int count,
        RTI_RoutingServiceEnvironment *env)
{
    struct DDS_DynamicData *sample;
    struct DDS_SampleInfo *info;
    int sampleLength;
    int i;
    struct DisAdapterStreamWriter *self =
            (struct DisAdapterStreamWriter*) stream_writer;

    if (self == 0 || self->cx == 0 || self->cx->sendBuffer == 0) {
        fprintf(stderr, "DisAdapterStreamWriter_write: invalid StreamWriter.\n");
        return 0;
    }
    if (self->msgInstance == 0) {
        fprintf(stderr,
                "DisAdapterStreamWriter_write: invalid message instance.\n");
        return 0;
    }
    for (i = 0; i < count; i++) {
        sample = (struct DDS_DynamicData*) sample_list[i];
        info = (struct
                DDS_SampleInfo*) (info_list == NULL ? NULL : info_list[i]);

        if (info != NULL && !info->valid_data) {
            continue;
        }

#ifdef ENABLE_DIS_DEBUG_MSGS
        if (RTI_RoutingServiceEnvironment_get_verbosity(env)
            >= RTI_ROUTING_SERVICE_VERBOSITY_INFO)
            printf("\nSerialization of sample for stream: %s starting\n",
                   self->streamName);
#endif

        sampleLength = DisParser_SerializeSample(
                sample,
                self->msgType,
                self->msgInstance,
                (RTI_INT8*) self->cx->sendBuffer,
                self->cx->maxMessageSize,
                env);

        if (sampleLength < 0) {
            return i;
        } else if (sampleLength == 0) {
            continue;
        }

#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("Serialization of sample for stream: %s, length: %d "
               "completed\n\n",
               self->streamName,
               sampleLength);
#endif

        if (!RTI_RoutingServiceSocket_socket_send(
                    self->cx->writeSocket,
                    &self->cx->sendAddr,
                    self->cx->sendBuffer,
                    sampleLength)) {
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Error sending sample");
            return i;
        }

        /* increment msgInstance for each sample sent */
        self->msgInstance++;
    }

    return i;
}

/*=========================================================================

    Connection methods: Internal methods to read and write from and to a socket
    It uses the SocketUtil methods.

 =========================================================================*/

int DisAdapterConnection_unblock(struct DisAdapterConnection *self)
{
    struct sockaddr_in sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(self->receivePort);
    sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (!RTI_RoutingServiceSocket_socket_send(
                self->writeSocket,
                &sockAddr,
                (char*) SOCKET_ADAPTER_UNBLOCK_MESSAGE,
                SOCKET_ADAPTER_UNBLOCK_MESSAGE_SIZE)) {
        return 0;
    }

    return 1;
}


/**
 * @brief The connection thread reads messages from a socket and associates them
 *        with a StreamReader based on the streamName (topicName).
 *
 * @param threadParam
 *
 */
void *DisAdapterConnection_run(void *threadParam)
{
    RTI_INT32 length;
    int error = 0;
    int msgType;
    DDS_Long bytesRead = 0;
    DDS_Long totalBytesRead = 0;
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) threadParam;
    struct DisAdapterStreamReader *streamReader = NULL;

    while (self->enabled) {
#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("\nCalling socket %d receive\n", self->receivePort);
#endif
        /* Receive new sample */
        length = (RTI_INT32) RTI_RoutingServiceSocket_socket_receive(
                self->readSocket,
                self->recvBuffer,
                self->maxMessageSize);
#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("Returned from socket receive\n");
#endif
        if (length == -1) {
            /* Error */
            continue;
        } else if (
                length == SOCKET_ADAPTER_UNBLOCK_MESSAGE_SIZE
                && !RTIOsapiMemory_compare(
                        self->recvBuffer,
                        SOCKET_ADAPTER_UNBLOCK_MESSAGE,
                        SOCKET_ADAPTER_UNBLOCK_MESSAGE_SIZE)) {
            /* Unblock message */
            continue;
        }

#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("Received DIS PDU of length %d\n", length);

        printf("buffer...\n");
        for (RTI_INT32 i = 0; i < length; ++i) {
            printf("%x ", (unsigned char) self->recvBuffer[i]);
        }
        printf("\n");
#endif

#if 0
        if (isascii(self->recvBuffer[8])) {
            self->recvBuffer[length] = 0;

            continue;
        }
#endif


        /* Obtain the header form the received DIS sample */
        long headerWord1;
        memcpy(&headerWord1, &self->recvBuffer[0], sizeof(long));
        /* headerWord1 = ntohl(headerWord1);*/
        DIS_PDU_Header *pHeader = (DIS_PDU_Header*) &(headerWord1);
        msgType = pHeader->m_ui8PDUType;

        streamReader = self->firstStreamReader;

#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("Iterating over streamReaders for msgType: %d\n", msgType);
        if (streamReader == NULL)
            fprintf(stderr, "  *** No streamreaders available!\n");
#endif

        while (streamReader != NULL) {
            if (streamReader->msgType == msgType) {
                if (RTIOsapiSemaphore_take(
                            streamReader->dynDataSem,
                            RTI_NTP_TIME_INFINITE)
                    != RTI_OSAPI_SEMAPHORE_STATUS_OK) {
                    fprintf(stderr, "Error taking StreamReader sem\n");
                    streamReader = streamReader->next;
                    continue;
                }

                /* We parse the sample */
                DDS_DynamicData *dynData = NULL;
                DDS_SampleInfo *sampleInfo = NULL;
                struct DisDynamicDataList* dynDataList =
                        streamReader->dynDataList;
                while (dynDataList != NULL) {
                    if (streamReader->dynDataList->inUse == RTI_FALSE) {
                        dynData = streamReader->dynDataList->dynData;
                        sampleInfo = streamReader->dynDataList->sampleInfo;

                        streamReader->dynDataList->inUse = RTI_TRUE;
                        break;
                    }
                    dynDataList = dynDataList->next;
                }
                /* if dynData == NULL, create a new one & add to the list */
                if (dynData == NULL) {
                    struct DDS_DynamicDataProperty_t dynamicDataProps =
                            DDS_DynamicDataProperty_t_INITIALIZER;
                    dynData = DDS_DynamicData_new(
                            streamReader->tc,
                            &dynamicDataProps);
                    sampleInfo = new DDS_SampleInfo;

                    dynDataList = (DisDynamicDataList*) malloc(
                            sizeof(DisDynamicDataList));
                    if (dynDataList == NULL || dynData == NULL
                        || sampleInfo == NULL) {
                        fprintf(stderr, "Error creating dynamic data list\n");
                        continue;
                    }
                    /* All samples created by this Adapter are valid */
                    sampleInfo->valid_data = DDS_BOOLEAN_TRUE;

                    dynDataList->dynData = dynData;
                    dynDataList->sampleInfo = sampleInfo;
                    dynDataList->inUse = RTI_FALSE;
                    dynDataList->next = streamReader->dynDataList;
                    streamReader->dynDataList = dynDataList;
                }
                if (!DisParser_ParseMessage(
                            dynData,
                            pHeader,
                            self->recvBuffer,
                            &bytesRead)) {
                    fprintf(stderr, "Error parsing message\n");
                    RTIOsapiSemaphore_give(streamReader->dynDataSem);

                    streamReader = streamReader->next;
                    continue;
                }

                /* Notify routing service */
#ifdef ENABLE_DIS_DEBUG_MSGS
                printf("processed %d of %d bytes\n", bytesRead, length);
                printf("Calling on_data_available for msgType: %d\n", msgType);
#endif
                streamReader->listener.on_data_available(
                        streamReader,
                        streamReader->listener.listener_data);
                /*
                 * We do not break here because we could have multiple
                 * StreamReaders per stream (topic)
                 */
            }

            streamReader = streamReader->next;
        }
    }

    return NULL;
}


void DisAdapterConnection_delete_stream_reader(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceStreamReader stream_reader,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) connection;
    struct DisAdapterStreamReader *streamReader =
            (struct DisAdapterStreamReader*) stream_reader;
    int error = 0;

    if (RTIOsapiSemaphore_take(streamReader->dynDataSem, RTI_NTP_TIME_INFINITE)
        != RTI_OSAPI_SEMAPHORE_STATUS_OK) {
        fprintf(stderr, "Error taking StreamReader sem\n");
        /* try anyway */
    }

    DisDynamicDataList *dynDataList = streamReader->dynDataList;
    while (dynDataList != NULL) {
        if (dynDataList->dynData != NULL) {
            DDS_DynamicData_delete(dynDataList->dynData);
            dynDataList->dynData = NULL;
            delete dynDataList->sampleInfo;
            dynDataList->sampleInfo = NULL;
        }
        DisDynamicDataList *dynDataListDel = dynDataList;
        dynDataList = dynDataList->next;
        free(dynDataListDel);
        dynDataListDel = NULL;
    }

    if (streamReader->streamName != NULL) {
        free(streamReader->streamName);
    }

    RTIOsapiSemaphore_delete(streamReader->dynDataSem);

    /* Remove StreamReader from connection list */
    self->streamReaderCount--;

    if (self->streamReaderCount == 0) {
        self->firstStreamReader = NULL;
    } else {
        if (streamReader->next) {
            streamReader->next->prev = streamReader->prev;
        }

        if (streamReader->prev) {
            streamReader->prev->next = streamReader->next;
        }
    }

    free(streamReader);
}


RTI_RoutingServiceStreamReader DisAdapterConnection_create_stream_reader(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceSession session,
        const struct RTI_RoutingServiceStreamInfo *stream_info,
        const struct RTI_RoutingServiceProperties *properties,
        const struct RTI_RoutingServiceStreamReaderListener *listener,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) connection;
    struct DDS_DynamicDataProperty_t dynamicDataProps =
            DDS_DynamicDataProperty_t_INITIALIZER;
    int ok = 0;
    int error;
    const char* msgTypeStr = NULL;
    struct DisAdapterStreamReader *streamReader = NULL;
    struct RTIOsapiSemaphoreProperty semProperties = {
        RTI_SEMAPHORE_THREAD_QUEUE_OPTION_FIFO,
        1
    };


#ifdef ENABLE_DIS_DEBUG_MSGS
    printf("\n    DisAdapterConnection_create_stream_reader.\n");
#endif

    streamReader = (DisAdapterStreamReader*) calloc(
            1,
            sizeof(struct DisAdapterStreamReader));
    if (streamReader == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        return NULL;
    }

    /* Cache the msgType */
    msgTypeStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "message_type");
    if (msgTypeStr == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Missing property 'message_type'");
        goto end;
    } else {
        streamReader->msgType = atoi(msgTypeStr);
    }
    streamReader->listener = *listener;

    /* Cache the streamName (topicName) */
    streamReader->streamName =
            (char*) malloc(strlen(stream_info->stream_name) + 1);
    if (streamReader->streamName == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        goto end;
    }
    strcpy(streamReader->streamName, stream_info->stream_name);

    self->verbosity = RTI_RoutingServiceEnvironment_get_verbosity(env);
    _verbosity = RTI_RoutingServiceEnvironment_get_verbosity(env);

    /* Create a DynamicData sample for this StreamReader */
    streamReader->tc =
            (struct DDS_TypeCode*) stream_info->type_info.type_representation;
    streamReader->dynDataList =
            (DisDynamicDataList*) malloc(sizeof(DisDynamicDataList));
    if (streamReader->dynDataList == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error creating dynamic data list");
        goto end;
    }
    streamReader->dynDataList->next = NULL;
    streamReader->dynDataList->dynData =
            DDS_DynamicData_new(streamReader->tc, &dynamicDataProps);
    streamReader->dynDataList->sampleInfo = new DDS_SampleInfo;
    if (streamReader->dynDataList->dynData == NULL
        || streamReader->dynDataList->sampleInfo == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error creating dynamic data sample");
        goto end;
    }
    streamReader->dynDataList->sampleInfo->valid_data = DDS_BOOLEAN_TRUE;
    streamReader->dynDataList->inUse = RTI_FALSE;
    streamReader->next = NULL;

    /* Create a semaphore to protect the dynamic data sample */
    streamReader->dynDataSem = RTIOsapiSemaphore_new(
            RTI_OSAPI_SEMAPHORE_KIND_BINARY,
            &semProperties);
    if (!streamReader->dynDataSem) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error initializing StreamReader semaphore");
        goto end;
    }

    streamReader->dynDataSemInit = RTI_TRUE;

    /* Insert StreamReader in connection list */
    if (self->firstStreamReader) {
        self->firstStreamReader->prev = streamReader;
        streamReader->next = self->firstStreamReader;
    }
    self->firstStreamReader = streamReader;
    self->streamReaderCount++;

    ok = 1;

end:

    if (!ok) {
        DisAdapterConnection_delete_stream_reader(
                connection,
                streamReader,
                env);
        return NULL;
    }

#ifdef ENABLE_DIS_DEBUG_MSGS
    printf("Created socket stream reader stream: %s, msgType: %d\n",
           streamReader->streamName,
           streamReader->msgType);
#endif


    return streamReader;
}


void DisAdapterConnection_delete_stream_writer(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceStreamWriter stream_writer,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) connection;
    struct DisAdapterStreamWriter *streamWriter =
            (struct DisAdapterStreamWriter*) stream_writer;

    if (streamWriter->streamName != NULL) {
        free(streamWriter->streamName);
    }

    /* Remove StreamWriter from connection list */
    self->streamWriterCount--;

    if (self->streamWriterCount == 0) {
        self->firstStreamWriter = NULL;
    } else {
        if (streamWriter->next) {
            streamWriter->next->prev = streamWriter->prev;
        }

        if (streamWriter->prev) {
            streamWriter->prev->next = streamWriter->next;
        }
    }

    free(streamWriter);
}

RTI_RoutingServiceStreamWriter DisAdapterConnection_create_stream_writer(
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceSession session,
        const struct RTI_RoutingServiceStreamInfo *stream_info,
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env)
{
    int ok = 0;
    const char* msgTypeStr = NULL;
    struct DisAdapterStreamWriter *streamWriter = NULL;
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) connection;

#ifdef ENABLE_DIS_DEBUG_MSGS
    printf("\n   DisAdapterConnection_create_stream_writer.\n");
#endif
    /* do not create a duplicate StreamWriter for an existing topic name */
    streamWriter = self->firstStreamWriter;
    while (streamWriter != NULL) {
        if (!strcmp(streamWriter->streamName, stream_info->stream_name)) {
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Duplicate topic requested");
            return NULL;
        }
        streamWriter = streamWriter->next;
    }

    streamWriter = (DisAdapterStreamWriter*) calloc(
            1,
            sizeof(struct DisAdapterStreamWriter));
    if (streamWriter == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        return NULL;
    }

    /* Cache the streamName (topicName) */
    streamWriter->streamName =
            (char*) malloc(strlen(stream_info->stream_name) + 1);
    if (streamWriter->streamName == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        goto end;
    }
    strcpy(streamWriter->streamName, stream_info->stream_name);

    /* Cache the msgType */
    msgTypeStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "message_type");
    if (msgTypeStr == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Missing property 'message_type'");
        goto end;
    } else {
        streamWriter->msgType = atoi(msgTypeStr);
    }

    /* initialize msgInstance */
    streamWriter->msgInstance = 1;

    streamWriter->cx = (struct DisAdapterConnection*) connection;

    /* Insert streamWriter in connection list */
    if (self->firstStreamWriter) {
        self->firstStreamWriter->prev = streamWriter;
        streamWriter->next = self->firstStreamWriter;
    }

    self->firstStreamWriter = streamWriter;
    self->streamWriterCount++;

    ok = 1;
end:
    if (!ok) {
        DisAdapterConnection_delete_stream_writer(
                connection,
                streamWriter,
                env);
        return NULL;
    }

#ifdef ENABLE_DIS_DEBUG_MSGS
    printf("Created socket stream writer stream: %s, msgType: %d\n",
           streamWriter->streamName,
           streamWriter->msgType);
#endif

    return streamWriter;
}

/* ========================================================================= */
/*                                                                           */
/* AdapterPlugin methods                                                     */
/*                                                                           */
/* ========================================================================= */

void DisAdapterPlugin_delete_connection(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        RTI_RoutingServiceConnection connection,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterConnection *self =
            (struct DisAdapterConnection*) connection;

    self->enabled = RTI_FALSE;

    if (self->readSocket > 0) {
        if (self->threadCreated) {
            DisAdapterConnection_unblock(self);

#ifdef RTI_WIN32
            WaitForSingleObject(self->thread, INFINITE);
#else
            pthread_join(self->thread, NULL);
#endif
        }
        /* Wait for the connection thread */
        RTI_RoutingServiceSocket_close_socket(self->readSocket);
        self->readSocket = -1;
    }

    if (self->writeSocket) {
        RTI_RoutingServiceSocket_close_socket(self->writeSocket);
        self->writeSocket = -1;
    }

    if (self->recvBuffer != NULL) {
        free(self->recvBuffer);
        self->recvBuffer = NULL;
    }

    if (self->sendBuffer != NULL) {
        free(self->sendBuffer);
        self->sendBuffer = NULL;
    }

    free(self);
}


RTI_RoutingServiceConnection DisAdapterPlugin_create_connection(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        const char *routing_service_name,
        const char *routing_service_group_name,
        const struct RTI_RoutingServiceStreamReaderListener
                *input_disc_listener,
        const struct RTI_RoutingServiceStreamReaderListener
                *output_disc_listener,
        const struct RTI_RoutingServiceTypeInfo **registeredTypes,
        int registeredTypeCount,
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterConnection* connection = NULL;
    int error;
    const char *host = NULL;
    const char *broadcastStr = NULL;
    const char *portStr = NULL;
    const char *hostIdStr = NULL;
    const char *maxMessageSizeStr = NULL;
    int port;
    bool broadcast;
    char ok = 0;
    RTI_RoutingServiceVerbosity verbosity = RTI_ROUTING_SERVICE_VERBOSITY_NONE;
#ifndef RTI_WIN32
    pthread_attr_t threadAttr;
#endif

    connection = (DisAdapterConnection*) calloc(
            1,
            sizeof(struct DisAdapterConnection));
    if (connection == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        goto end;
    }

    connection->readSocket = -1;
    connection->writeSocket = -1;
    connection->adapter = (struct DisAdapterPlugin*) adapter;


    verbosity = RTI_RoutingServiceEnvironment_get_verbosity(env);

    /* Host where the adapter will send data */
    host = RTI_RoutingServiceProperties_lookup_property(properties, "host");
    if (host == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Missing property 'host'");
        goto end;
    }

    /* Whether to allow broadcast */
    broadcastStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "broadcast");
    if (broadcastStr == NULL) {
#ifdef ENABLE_DIS_DEBUG_MSGS
        printf("DisAdapterPlugin_create_connection:Broadcast not specified, "
               "defaults to enabled.\n");
#endif
        broadcast = true;
    } else {
        if (atoi(broadcastStr) == 0) {
            broadcast = false;
        } else {
            broadcast = true;
        }
    }


    /* UDP port where the StreamWriters will send data  */
    portStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "send_port");
    if (portStr == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Missing property 'send_port', using 3001");
        port = 3001;
    } else {
        port = atoi(portStr);
        if (port <= 0 || port > 65535) {
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Incorrect value for property 'send_port'");
            goto end;
        }
    }

    /* Construct the address where the StreamWriters will send data */
    connection->sendAddr.sin_family = AF_INET;
    connection->sendAddr.sin_port = htons((unsigned short) port);

    if (!RTI_RoutingServiceSocket_get_host_by_name(
                &connection->sendAddr.sin_addr,
                host)) {
        RTI_RoutingServiceEnvironment_set_error(env, "Incorrect host name");
        goto end;
    }

    /* UDP port in which the adapter will receive data */
    portStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "receive_port");
    if (portStr == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Missing property 'receive_port', using 3000");
        goto end;
    } else {
        port = atoi(portStr);
        if (port <= 0 || port > 65535) {
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Incorrect value for property 'receive_port'");
            goto end;
        }
    }
    connection->receivePort = port;

    /* Maximum message size */
    maxMessageSizeStr = RTI_RoutingServiceProperties_lookup_property(
            properties,
            "message_max_size");
    if (maxMessageSizeStr == NULL) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Missing property 'message_max_size'");
        goto end;
    } else {
        connection->maxMessageSize = atoi(maxMessageSizeStr);
        if (connection->maxMessageSize <= 0) {
            RTI_RoutingServiceEnvironment_set_error(
                    env,
                    "Incorrect value for property 'message_max_size'");
            goto end;
        }
    }

    /* Create message buffers */
    connection->recvBuffer =
            (char*) malloc(connection->maxMessageSize * sizeof(char));
    if (connection->recvBuffer == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        goto end;
    }

    connection->sendBuffer =
            (char*) malloc(connection->maxMessageSize * sizeof(char));
    if (connection->sendBuffer == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        goto end;
    }

    /* Create the socket that will be used to send/receive data */
    connection->readSocket = RTI_RoutingServiceSocket_create_udp_socket(
            connection->receivePort,
            false);
    if (connection->readSocket < 0) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error creating data socket");
        goto end;
    }

    /*
     * Create write socket that will be used to send data and wake up the
     * connection (read) thread
     */
    connection->writeSocket =
            RTI_RoutingServiceSocket_create_udp_socket(0, broadcast);
    if (connection->writeSocket < 0) {
        RTI_RoutingServiceEnvironment_set_error(
                env,
                "Error creating unblock socket");
        goto end;
    }

    /* Create the connection thread that will read from data the UDP socket */
#ifdef RTI_WIN32
    connection->thread = (HANDLE) _beginthread(
            (void(__cdecl*)(void*)) DisAdapterConnection_run,
            0,
            (void*) connection);
    error = !connection->thread;
#else
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);

    error = pthread_create(
            &connection->thread,
            &threadAttr,
            DisAdapterConnection_run,
            (void*) connection);
#endif

    if (error) {
        RTI_RoutingServiceEnvironment_set_error(env, "Error creating thread");
        goto end;
    }

    connection->enabled = RTI_TRUE;
    connection->threadCreated = RTI_TRUE;

    ok = 1;

end:
    if (!ok && connection != NULL) {
        DisAdapterPlugin_delete_connection(adapter, connection, env);
        return NULL;
    }

    return connection;
}


void DisAdapterPlugin_delete(
        struct RTI_RoutingServiceAdapterPlugin *adapter,
        RTI_RoutingServiceEnvironment *env)
{
    free(adapter);
}


struct RTI_RoutingServiceAdapterPlugin *DisAdapterPlugin_create(
        const struct RTI_RoutingServiceProperties *properties,
        RTI_RoutingServiceEnvironment *env)
{
    struct DisAdapterPlugin *adapter = NULL;
    struct RTI_RoutingServiceVersion version = RTI_ROUTING_SERVICE_VERSION;

    adapter = (DisAdapterPlugin*) calloc(1, sizeof(struct DisAdapterPlugin));

    if (adapter == NULL) {
        RTI_RoutingServiceEnvironment_set_error(env, "Memory allocation error");
        return NULL;
    }

    RTI_RoutingServiceAdapterPlugin_initialize(&adapter->base);

    adapter->base.plugin_version = version;

    /*
     * Assign the function pointers
     */
    adapter->base.adapter_plugin_delete = DisAdapterPlugin_delete;

    /* connection related methods */
    adapter->base.adapter_plugin_create_connection =
            DisAdapterPlugin_create_connection;
    adapter->base.adapter_plugin_delete_connection =
            DisAdapterPlugin_delete_connection;

    /* reader related methods */
    adapter->base.connection_create_stream_reader =
            DisAdapterConnection_create_stream_reader;
    adapter->base.connection_delete_stream_reader =
            DisAdapterConnection_delete_stream_reader;
    adapter->base.stream_reader_read = DisAdapterStreamReader_read;
    adapter->base.stream_reader_return_loan =
            DisAdapterStreamReader_return_loan;

    /* writer related methods */
    adapter->base.connection_create_stream_writer =
            DisAdapterConnection_create_stream_writer;
    adapter->base.connection_delete_stream_writer =
            DisAdapterConnection_delete_stream_writer;
    adapter->base.stream_writer_write = DisAdapterStreamWriter_write;

    return (struct RTI_RoutingServiceAdapterPlugin*) adapter;
}

#undef ROUTER_CURRENT_SUBMODULE
