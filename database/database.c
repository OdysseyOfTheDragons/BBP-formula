#include "database.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

long unsigned int database_init()
{
	// Try to open the database_position.txt file. If it can't be opened
	// for reading, open it for read/write to create it.
	FILE *f = fopen(DATABASE_POSITION, "r");

	if (f != NULL) {
		// The file exists
		int start;
		if (fscanf(f, "%d", &start) == 0) {
			perror("[Database] DATABASE_POSITION empty.");
			exit(errno);
		}

		fclose(f);
		return start;
	}

	printf("[Database] DATABASE_POSITION does not exist.\n");

	f = fopen(DATABASE_POSITION, "w");
	if (f == NULL) {
		perror("[Database] Can't create DATABASE_POSITION file.");
		exit(errno);
	}

	fprintf(f, "%d", 0);
	fclose(f);

	printf("[Database] DATABASE_POSITION created.\n");
	return 0;
}

int database_get() {
	FILE* f = fopen(DATABASE_POSITION, "r");
	if (f == NULL) {
		perror("[Database] DATABASE_POSITION not found to read.");
		exit(errno);
	}

	int start;
	if (fscanf(f, "%d", &start) == 0) {
		perror("[Database] DATABASE_POSITION is empty.");
		exit(errno);
	}

	fclose(f);
	return start;
}

void database_update(int start)
{
	printf("[Database] Update DATABASE_POSITION to %d.\n", start);
	FILE *f = fopen(DATABASE_POSITION, "w");
	if (f == NULL) {
		perror("[Database] No DATABASE_POSITION file.");
		exit(errno);
	}

	fprintf(f, "%d", start);
	fclose(f);
}

void database_store_hex(int start, int number, char *digits)
{
	// To start at 500 million, to calculate 1000, and to have the path
	// to the file isn't more than 50 characters, so a length of
	// 256 is enough
	char filename[256] = { '\0' };
	sprintf(filename, "%s/%d_%d.txt", DATABASE_OUTPUT, start, number);

	printf("[Database] Store hex from %d to %d in file %s.\n",
	       start, start + number, filename);

	// We create the file and save the digits
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		perror("[Database] Can't create storage file.");
		exit(errno);
	}

	fprintf(f, "%s", digits);
	fclose(f);

	// We save the file in the files list
	f = fopen(DATABASE_HEX_LIST, "a");
	if (f == NULL) {
		perror("[Database] Can't write to DATABASE_HEX_LIST file.");
		exit(errno);
	}

	fprintf(f, "%s\n", filename);
	fclose(f);
}
