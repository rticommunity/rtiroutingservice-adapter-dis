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
/* RTI Routing Service STANAG 4586 Socket Adapter                            */
/* ========================================================================= */
/*                                                                           */
/* SocketUtil.h                                                              */
/*                                                                           */
/* ========================================================================= */

#ifndef SocketUtil_h
#define SocketUtil_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef RTI_WIN32
    #define DllExport __declspec(dllexport)
    #include <Winsock2.h>
#else
    #define DllExport
    #include <sys/select.h>
    #include <fcntl.h>
    #include <netinet/tcp.h>
    #include <netdb.h>
    #include <sys/ioctl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if defined(RTI_WIN32)
    #define RTI_RoutingServiceSocket_get_error WSAGetLastError
#else
    #define RTI_RoutingServiceSocket_get_error errno
#endif

int RTI_RoutingServiceSocket_create_udp_socket(
        unsigned short bindPort,
        bool broadcast);

int RTI_RoutingServiceSocket_get_host_by_name(
        struct in_addr *address,
        const char *hostName);

int RTI_RoutingServiceSocket_socket_receive(
        int sock,
        char *buffer,
        int bufferLength);

int RTI_RoutingServiceSocket_socket_send(
        int sock,
        const struct sockaddr_in *sockAddr,
        char* buffer,
        int length);

void RTI_RoutingServiceSocket_close_socket(int sd);

void *RTI_RoutingServiceUtil_resize_buffer(
        void *buffer,
        int currentLength,
        int newLength,
        int elementSize);

#ifdef __cplusplus
}
#endif

#endif /* SocketUtil_h */
