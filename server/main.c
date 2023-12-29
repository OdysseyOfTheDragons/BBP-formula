#include "server.h"

/// Get the current IP the server is listening on.
///
/// @return The IP of the server
char* get_ip() {
	char host_buffer[256];

	if (gethostname(host_buffer, sizeof(host_buffer)) < 0) {
		perror("[Server] Unable to access host name.");
		exit(errno);
	}

	// Retrieve host information
	struct hostent* host_entry = gethostbyname(host_buffer);
	if (host_entry == NULL) {
		perror("[Server] Unable to get host by name.");
		exit(errno);
	}

	// Get ASCII IP
	char* ip = inet_ntoa(*((struct in_addr*)
				host_entry->h_addr_list[0]));
	if (ip == NULL) {
		perror("[Server] Unable to access IP.");
		exit(errno);
	}

	return ip;
}

int main(void)
{
	printf("Server starting...\n");

	// Print the port and the IP
	printf("[Server is on %s:%d]\n\n", get_ip(), PORT);

	// sockfd is a socket file descriptor
	// serv_addr is the socket adress, needed in the bind function
	int sockfd, newsockfd;
	struct sockaddr_in serv_addr, client_addr;

	// The client request length
	unsigned int client_len;

	// Socket creation
	// If socket() returns -1, there is an error
	//
	// AF_INET is for IPV4
	// SOCK_STREAM is for TCP
	// 0 means default protocol
	if ((sockfd = socket(COM_STANDARD, COM_TYPE, COM_PROTOCOL)) < 0) {
			perror("[Server] Unable to create sockets.\n");
			exit(errno);
	}

	// Server only: binding
	serv_addr.sin_family = COM_STANDARD;
	serv_addr.sin_addr.s_addr = htonl(COM_ORIGIN);
	serv_addr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("[Server] Unable to bind to local address.");
		exit(errno);
	}

	// Listen to a specific number of clients at a time
	listen(sockfd, MAX_CLIENTS);

	// Listen to the clients
	while (true) {
		client_len = sizeof(client_addr);
		newsockfd = accept(
			sockfd,
			(struct sockaddr*)&client_addr,
			&client_len
		);

		if (newsockfd < 0) {
			perror("[Server] Unable to accept new client.");
			exit(errno);
		}

		if (fork() == 0) {
			// We fork the client to handle multiple clients at a time

			// Close the old socket, since all other connections are through
			// the new one.
			close(sockfd);

			char* send_msg = "A welcome from the server!";

			// The last 0 is for the flags
			send(newsockfd, send_msg, strlen(send_msg), 0);

			// Receive data
			char buf[1024] = {'\0'};
			recv(newsockfd, buf, 1024 - 1, 0);
			printf("> %s\n", buf);
			close(newsockfd);

			exit(EXIT_SUCCESS);
		}

		close(newsockfd);
	}

	return EXIT_SUCCESS;
}
