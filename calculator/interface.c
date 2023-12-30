/**
 * @file
 * This file aims to be the interface, which calculates a number of digits
 * of \f$\pi\f$ using parallelism.
 */

#include "mathematics/mathematics.h"
#include "algorithm.h"
#include "converter/converter.h"
#include <stdlib.h>
#include <omp.h>

/// Calculates `number` digits, starting from `start` (included).
///
/// @param start The first digit to calculate
/// @param number The number of digits tocalculate after start
/// @return The hex string of \f$\pi\f$ digits
char *calculate_digits(const int start, const int number)
{
	const int number_plus = number + 1;
	const int number_and_start = start + number;

	char *hex = (char *)calloc(number_plus, sizeof(char));

#pragma omp parallel shared(hex)
	{
#pragma omp for nowait
		for (unsigned int i = start; i < number_and_start; i++) {
#pragma omp atomic
			hex[i - start] += convert_digit(pi(i));
		}
	}

	hex[number_plus] = '\0';
	return hex;
}
