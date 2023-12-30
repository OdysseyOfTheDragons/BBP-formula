#include "server.h"
#include "communications.h"
#include "database/database.h"

/// Get the current IP the server is listening on.
///
/// @return The IP of the server
char *get_ip()
{
	char host_buffer[256];

	if (gethostname(host_buffer, sizeof(host_buffer)) < 0) {
		perror("[Server] Unable to access host name.");
		exit(errno);
	}
	// Retrieve host information
	struct hostent *host_entry = gethostbyname(host_buffer);
	if (host_entry == NULL) {
		perror("[Server] Unable to get host by name.");
		exit(errno);
	}
	// Get ASCII IP
	char *ip = inet_ntoa(*((struct in_addr *)
			       host_entry->h_addr_list[0]));
	if (ip == NULL) {
		perror("[Server] Unable to access IP.");
		exit(errno);
	}

	return ip;
}

/// Get the number of digits the client must compute, based on the starting
/// digit.
///
/// @param start The first digit to compute
/// @return The number of digits to compute
unsigned int get_number(unsigned int start)
{
	if (start < 100000) {
		return 10000;
	}
	if (start < 500000) {
		return 5000;
	}
	if (start < 1000000) {
		return 1000;
	}
	if (start < 5000000) {
		return 500;
	}
	if (start < 10000000) {
		return 10;
	}
	return 5;
}

/// @todo
/// TODO: The current system to know the starting digit isn't enough:
/// for example, if a client is shut down (error or the user wants to stop),
/// the server won't know and will skip those digits.
///
/// A way to improve that would be, on connection loss, to go back to an old
/// starting point (which means keeping track of the file and its
/// evolution). Or else, the database_position.txt file can be made
/// with a list of `start:end` with `end=start+number`, and once in a
/// time, when we do `database_get()`, we check if there is a hole. If there
/// is, we insert the missing line and return the start. But this means
/// the `database_get()` is the function which returns the number of digits
/// to compute, if it must store the number too.
///
/// The flaw is, we can't add the `start:end` line on `database_get()`,
/// for the same reasons as before. We must do that in `database_store_hex()`.
/// 
/// Then, the solution I have in mind, is a database status in two files:
/// - the already existing `DATABASE_POSITION` file, which acts as a counter.
/// - a new `DATABASE_HISTORY` file, which is a `start:end` list,
/// one item per line. Once every threshold, for example every 100000,
/// the `database_get()` function parses this file to search for holes and
/// returns the start and number of digits missing.
///
/// This technique means multiple things:
/// - the `database_store_hex()` call must append the line `start:end`
/// where it should come, which may be a problem if multiple clients are
/// connected at the same time, and some are quicker to do calculations.
/// A way to solve that is to parse - yet another time - the file for every
/// insertion, to insert it in good place. This would solve the good insertion
/// place of the `database_get()` call when there is a hole, but this would
/// make every save slower and longer.
/// - For better performances, it is better that once a hole is patched,
/// the surroundings are merged into a single line. That way, the parser
/// will have less to compute, and it will be faster.

/// The server main function.
int main(void)
{
	printf("[Server starting...]\n");

	// Print the port and the IP
	printf("[Server is on %s:%d]\n", get_ip(), PORT);

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

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("[Server] Unable to bind to local address.");
		exit(errno);
	}
	// Listen to a specific number of clients at a time
	listen(sockfd, MAX_CLIENTS);
	printf("[Server listening to clients...]\n");

	// Get the digits to calculate
	int starting_digits = database_init();

	// Listen to the clients
	while (true) {
		client_len = sizeof(client_addr);
		newsockfd = accept(sockfd,
				   (struct sockaddr *)&client_addr,
				   &client_len);

		if (newsockfd < 0) {
			perror("[Server] Unable to accept new client.");
			exit(errno);
		} else {
			printf("[Server] New client connected.\n");
		}

		if (fork() == 0) {
			// We fork the client to handle multiple clients at a time

			// Close the old socket, since all other connections are through
			// the new one.
			close(sockfd);

			// We loop to get all messages each time
			bool quit_loop = false;
			while (!quit_loop) {
				// In the send() and rec() functions, 
				// the last 0 is for the flags,
				// flags I do not use.

				// We start by receiving the sent messages.
				// - API_GET_POS
				// - API_STORE

				// The maximum length of a message is around 1050, so we
				// create a bucket buffer of 4096 to be large.
				char buf[API_LENGTH] = { '\0' };

				// The length of the receiving is the total length -1
				// because the '\0' is not counted.
				recv(newsockfd, buf, API_LENGTH - 1, 0);
				if (strlen(buf) == 0) {
					quit_loop = true;
					continue;
				}
				// We get what is the request
				if (startswith(buf, API_GET_POS)) {
					printf("[Server] API_GET_POS\n");

					// We send an answer
					starting_digits = database_get();
					int number_of_digits =
					    get_number(starting_digits);

					char send_msg[API_LENGTH] = { '\0' };
					sprintf(send_msg, "%s%d|%d",
						API_CALC_DIGITS,
						starting_digits,
						number_of_digits);

					send(newsockfd, send_msg,
					     strlen(send_msg), 0);

					// Update the database
					starting_digits += number_of_digits;
					database_update(starting_digits);
				} else if (startswith(buf, API_STORE)) {
					printf("[Server] API_STORE\n");

					// We print the answer
					// TODO: store it

					char *start =
					    (char *)malloc(API_LENGTH *
							   sizeof(char));
					char *number =
					    (char *)malloc(API_LENGTH *
							   sizeof(char));
					char *digits =
					    (char *)malloc(API_LENGTH *
							   sizeof(char));

					split(buf, API_STORE, &start, &number,
					      &digits);

					// We update the database
					database_store_hex(atoi(start),
							   atoi(number),
							   digits);
				} else {
					printf
					    ("[Server] Unknown command: %s.\n",
					     buf);
				}
			}

			close(newsockfd);

			exit(EXIT_SUCCESS);
		}

		close(newsockfd);
	}

	return EXIT_SUCCESS;
}
