#include "server/server.h"
#include "calculator/interface.h"

int main() {
	// For a complete understanding of the notations, please read
	// the content of `server/main.c`.
	
	int sockfd;
	struct sockaddr_in serv_addr;

	if ((sockfd = socket(COM_STANDARD, COM_TYPE, COM_PROTOCOL)) < 0) {
		perror("[Client] Unable to create socket.");
		exit(errno);
	}

	serv_addr.sin_family = COM_STANDARD;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.1.1");
	serv_addr.sin_port = htons(PORT);

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("[Client] Unable to connect to server.");
		exit(errno);
	}

	char* send_msg = "A welcome from the client!";
	send(sockfd, send_msg, strlen(send_msg), 0); // last 0 is for
												 // the flags

	// Receive data
	char buf[1024] = {'\0'};
	recv(sockfd, buf, 1024 - 1, 0);
	printf("> %s\n", buf);

	close(sockfd);

	return EXIT_SUCCESS;
}
