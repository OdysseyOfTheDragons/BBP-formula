#include "server.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Server starting...\n");

	// sockfd is a socket file descriptor
	// my_addr is the socket adress, needed in the bind function
	struct sockaddr_in my_addr;
	int sockfd;

	// Socket creation
	// If socket() returns -1, there is an error
	if ((sockfd = socket(COM_STANDARD, COM_TYPE, 0)) < 0) {
			perror("[Server] Socker creation error\n");
			exit(EXIT_FAILURE);
	}

	// Server only: binding
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_addr.s_addr = inet_addr(IP);

	return EXIT_SUCCESS;
}
