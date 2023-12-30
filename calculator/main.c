/**
 * @file
 * A test file, to check whether the algorithm works as needed.
 */

#include "mathematics/mathematics.h"
#include "algorithm.h"
#include "converter/converter.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/// The number of decimals we want to calculate, and print to screen.
#define N 10000

/// The number of cases in the array.
#define Nplus (N + 1)

int main(void)
{
	char hex[Nplus] = { '\0' };

	printf("Starting calculating pi decimals:\n");

#pragma omp parallel shared(hex)
	{
#pragma omp for nowait
		for (unsigned int i = 0; i < N; i++) {
			// printf("\r> %d", i);

#pragma omp atomic
			hex[i] += convert_digit(pi(i));
		}
	}
	printf("\n\n");

	hex[N] = '\0';

//      char *str = convert(hex);
	printf("pi = %s\n\n", hex);
//      printf("pi = %s\n", str);

//      free(str);

	return 0;
}
