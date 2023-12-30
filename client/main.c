#include "server/server.h"
#include "server/communications.h"
#include "calculator/interface.h"

int main()
{
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

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)
	    ) < 0) {
		perror("[Client] Unable to connect to server.");
		exit(errno);
	}

	for (;; /* int iter = 0; iter < 10; iter++ */) {
		// Get the digits to calculate
		send(sockfd, API_GET_POS, strlen(API_GET_POS), 0);

		// Receive the data
		char get_msg[API_LENGTH] = { '\0' };
		recv(sockfd, get_msg, API_LENGTH - 1, 0);

		if (startswith(get_msg, API_CALC_DIGITS)) {
			// Get start and number

			char *start; // = (char *)malloc(API_LENGTH * sizeof(char));
			char *number; // = (char *)malloc(API_LENGTH * sizeof(char));
			split(get_msg, API_CALC_DIGITS, &start, &number, NULL);

			int s = atoi(start);
			int n = atoi(number);

			printf("[Client] Compute %d digits starting from %d.\n",
					n, s);

			char *digits = calculate_digits(s, n);

			// Send this to the server
			char send_msg[API_LENGTH] = { '\0' };
			sprintf(send_msg, "%s%d|%d|%s", API_STORE, s,
				n, digits);

			if (strlen(send_msg)) {
				// We do not send empty messages (it happens sometimes)
				send(sockfd, send_msg, strlen(send_msg), 0);
			}

			free(digits);
		} else {
			printf("[Client] Unknown command: %s.\n", get_msg);
		}
	}

	close(sockfd);

	return EXIT_SUCCESS;
}
