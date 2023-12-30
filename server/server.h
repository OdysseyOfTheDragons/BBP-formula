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
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/// The IP of the server
#define IP "0.0.0.0"

/// The port on which the server listens.
#define PORT 59081

/// The standard communication:
/// * `AF_LOCAL` for connections on the same host;
/// * `AF_INET` for communication over IPv4.
#define COM_STANDARD AF_INET

/// The communication type:
/// * `SOCK_STREAM` for reliable connections;
/// * `SOCK_DGRAM` for unreliable, connectionless relations.
#define COM_TYPE SOCK_STREAM

/// The specific protocol to use.
/// * `0` for default
#define COM_PROTOCOL 0

/// The host origins that are accepted.
#define COM_ORIGIN INADDR_ANY

/// The maximum number of clients the server can handle at a time.
#define MAX_CLIENTS 5
#endif
