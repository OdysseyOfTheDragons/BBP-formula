/**
 * @file
 * The implementation of the BBP formula.
 */

#include "algorithm.h"
#include "mathematics/mathematics.h"

/// The precision where we are nearly a hundred percent sure the calculated
/// digit is the good one. The lower this value is, the more precise the
/// digit will be.
/// But at the same time, please recall that the lower the value is, the
/// longer the computations will take.
#define PRECISION 1.0e-17

// To be faster, the variables are declared before use
// In sn()
// In pi()

/// Calulates the \f$Sn`f$ term of the \f$N\f$-th digit with the value `a`.
///
/// @param N The place of the digit to calculate
/// @param a A given parameter, coming from the formula
/// @return The sum desired
static long double sn(unsigned int N, int a)
{
	long double sum;
	unsigned int k;
	long double eight;
	long double numerator;
	long double coeff;

	sum = 0;

	for (k = 0; k < N; k++) {
		eight = 8 * k + a;
		numerator = _pow_modular(16, N - k, eight);

		coeff = numerator / eight;
		sum += coeff - (int)coeff;
		sum -= (int)sum;
	}

	while (1) {
		coeff = _pow(16, N - k) / (8 * k + a);
		if (coeff < PRECISION) {
			break;
		}

		sum += coeff - (int)coeff;
		sum -= (int)sum;

		k++;
	}

	return sum;
}

long double pi(unsigned int N)
{
	long double sn_1;
	long double sn_4;
	long double sn_5;
	long double sn_6;
	long double total;

	sn_1 = sn(N, 1);
	sn_4 = sn(N, 4);
	sn_5 = sn(N, 5);
	sn_6 = sn(N, 6);

	total = 4 * sn_1 - 2 * sn_4 - sn_5 - sn_6;

	return total - (int)total + 1.0;
}
