#include "communications.h"
#include <string.h>
#include <stdio.h>

bool startswith(char *str, char *prefix)
{
	return strncmp(prefix, str, strlen(prefix)) == 0;
}

void split(char *str, char *prefix, char **part1, char **part2, char **part3)
{
	long unsigned int prefix_length = strlen(prefix);

	// If the prefix is longer than the string, we do nothing
	if (strlen(str) < prefix_length) {
		*part1 = *part2 = *part3 = NULL;
		return;
	}
	// Then we create a pointer to the beginning of the string, without
	// the prefix.
	str = &str[prefix_length];

	// We split the string a first time, and 2 more times then.
	char *pointer = strtok(str, "|");

	if (pointer) {
		*part1 = pointer;
	}

	pointer = strtok(NULL, "|");
	if (pointer) {
		*part2 = pointer;
	}

	if (pointer == NULL || part3 == NULL) {
		return;
	}

	pointer = strtok(NULL, "|");
	if (pointer) {
		*part3 = pointer;
	}
}
