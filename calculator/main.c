/**
 * @file
 * A test file, to check whether the algorithm works as needed.
 */

#include "mathematics/mathematics.h"
#include "algorithm.h"
#include "converter/converter.h"
#include <stdio.h>
#include <stdlib.h>

/// The number of decimals we want to calculate, and print to screen.
#define N 100

int main(void)
{
	char *hex = (char *)malloc((N + 1) * sizeof(char));

	printf("Starting calculating pi decimals:\n");
	for (unsigned int i = 0; i < N; i++) {
		printf("\r> %d", i);
		hex[i] = convert_digit(pi(i));
	}
	printf("\n\n");

	hex[N] = '\0';

	char *str = convert(hex);
	printf("pi = %s\n", str);

	free(hex);
	free(str);

	return 0;
}
