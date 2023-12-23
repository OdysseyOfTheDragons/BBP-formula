/**
 * @file
 * Import all the functions the servers may need, and that aren't
 * related to this specific project. Which means, the following
 * libraries are imported because they are needed in every socket
 * server.
 */

#ifndef SERVER
#define SERVER
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/// The port on which the server listens.
#define PORT 2222

/// The standard communication:
/// * `AF_LOCAL` for connections on the same host;
/// * `AF_INET` for communication over IPv4.
#define COM_STANDARD AF_INET

/// The communication type:
/// * `SOCK_STREAM` for reliable connections;
/// * `SOCK_DGRAM` for unreliable, connectionless relations.
#define COM_TYPE SOCK_STREAM

/// The host origins that are accepted.
#define COM_ORIGIN INADDR_ANY
#endif
