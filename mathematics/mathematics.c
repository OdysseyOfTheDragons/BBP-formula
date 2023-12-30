/**
 * @file
 * Provides useful functions, that are faster than the base functions from
 * `<math.h>`.
 */

#include "mathematics.h"

// For faster results, the variables are declared ahead
// in _pow()
// unsigned int base;
// in _pow_modular()

long double _pow(int a, int k)
{
	long double pow_result;

	pow_result = 1.0;
	// base = a;

	if (k < 0) {
		a = 1.0 / a;
		k = -k;
	}

	while (k > 0) {
		// if (k % 2 == 1) {
		if ((k & 1) > 0) {
			pow_result *= a;
			k--;
		}

		a *= a;
		k /= 2;		// k >>= 1;     // divide by two
	}

	return pow_result;
}

long int _pow_modular(int a, int k, int r)
{
	// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
	if (r == 1) {
		return 0;
	}

	long int mod_result;

	mod_result = 1;
	a = a % r;
	while (k > 0) {
		if ((k & 1) > 0) {
			mod_result = (mod_result * a) % r;
		}

		k /= 2;		// k >>= 1
		a = (a * a) % r;
	}

	return mod_result;
}

double _abs(double a)
{
	if (a < 0) {
		return -a;
	}
	return a;
}

int _floor(long double val)
{
	return (int)val - (val < (int)val);
}
