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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef RTI_WIN32
    #include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "SocketUtil.h"

/**
 * Creates and bind an UDP socket
 */
int RTI_RoutingServiceSocket_create_udp_socket(
        unsigned short bindPort,
        bool broadcast)
{
    struct sockaddr_in sockAddr;
    int sd = -1;
    int bcast = 1;

#if defined(RTI_WIN32)
    sd = WSASocket(
            AF_INET,
            SOCK_DGRAM,
            0 /*protocol*/,
            NULL /*protocolInfo*/,
            0 /*group*/,
            0 /*dwFlags*/);
#else
    sd = socket(AF_INET, SOCK_DGRAM, 0 /*protocol*/);

    if (sd > 0) {
        /* close the socket in the child processes that have been
           "exec"'ed by the process that opened the socket */
        fcntl(sd, F_SETFD, FD_CLOEXEC);
    }
#endif

    if (sd <= 0) {
        return sd;
    }

    if (broadcast == true) {
#ifdef RTI_WIN32
        /* Set socket to allow broadcast */
        if (setsockopt(
                    sd,
                    SOL_SOCKET,
                    SO_BROADCAST,
                    (const char*) &bcast,
                    sizeof(bcast))
            < 0)
#else
        /* Set socket to allow broadcast */
        if (setsockopt(
                    sd,
                    SOL_SOCKET,
                    SO_BROADCAST,
                    (void*) &bcast,
                    sizeof(bcast))
            < 0)
#endif

        {
            sd = -1;
            return sd;
        }
    }

    /* Bind to the socket */
    memset(&sockAddr, 0, sizeof(struct sockaddr_in));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(bindPort);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Bind our name to the passed socket. */
    if (bind(sd, (struct sockaddr*) (&sockAddr), sizeof(struct sockaddr_in))
        != 0) {
#if defined(RTI_WIN32) || defined(RTI_WINCE)
        closesocket(sd);
#else
        close(sd);
#endif
        return -1;
    }

    return sd;
}

/**
 * Destroys an UDP socket
 */
void RTI_RoutingServiceSocket_close_socket(int sd)
{
#if defined(RTI_WIN32) || defined(RTI_WINCE)
    closesocket(sd);
#else
    close(sd);
#endif
}

/**
 * Gets the IP address of a host
 */
int RTI_RoutingServiceSocket_get_host_by_name(
        struct in_addr *address,
        const char* hostName)
{
    struct hostent* hostEntry = NULL;

    hostEntry = (struct hostent*) gethostbyname((char*) hostName);
    if (hostEntry == NULL) {
        return 0;
    }

    memcpy(address, hostEntry->h_addr_list[0], hostEntry->h_length);
    return 1;
}

int RTI_RoutingServiceSocket_socket_receive(
        int sock,
        char *buffer,
        int bufferLength)
{
    int length;
    struct sockaddr_in ipSource;
    unsigned int ipSourceSize = sizeof(struct sockaddr_in);
#if defined(RTI_WIN32)
    int flags = 0; /* don't care about flag, but can't provide NULL */
    WSABUF recvBuffer;

    recvBuffer.buf = buffer;
    recvBuffer.len = bufferLength;
#endif

#if defined(RTI_WIN32) || defined(RTI_WINCE)
    if (WSARecvFrom(
                (SOCKET) sock,
                &recvBuffer,
                1,
                (LPDWORD) &length,
                (LPDWORD) &flags,
                (struct sockaddr*) &ipSource,
                (LPINT) &ipSourceSize,
                NULL,
                NULL)
        != 0) {
        length = -1;
    }
#else
    length = recvfrom(
            sock,
            buffer,
            bufferLength,
            0,
            (struct sockaddr*) &ipSource,
            &ipSourceSize);
#endif

    return length;
}


int RTI_RoutingServiceSocket_socket_send(
        int sock,
        const struct sockaddr_in* sockAddr,
        char *buffer,
        int length)
{
#ifdef RTI_WIN32
    int bytesWritten;
    WSABUF sendBuffer;

    sendBuffer.buf = buffer;
    sendBuffer.len = length;

    if (WSASendTo(
                sock,
                &sendBuffer,
                1,
                (LPDWORD) &bytesWritten,
                0,
                (SOCKADDR*) sockAddr,
                sizeof(struct sockaddr_in),
                NULL,
                NULL)
                == SOCKET_ERROR
        || bytesWritten != length) {
        return 0;
    }
#else
    if (sendto(sock,
               buffer,
               length,
               0,
               (struct sockaddr*) sockAddr,
               sizeof(struct sockaddr_in))
        != length) {
        return 0;
    }
#endif

    return 1;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
