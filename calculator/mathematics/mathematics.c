#include "mathematics/mathematics.h"

// For faster results, the variables are declared ahead
// in _pow()
long double pow_result;
long double base;
// in _pow_modular()
long int mod_result;

long double _pow(int a, int k) {
	pow_result = 1.0;
	base = a;

	if (k < 0) {
		base = 1.0 / a;
		k = -k;
	}

	while (k > 0) {
		if (k % 2 == 1) {
			pow_result *= base;
			k--;
		}

		base *= base;
		k >>= 1; // divide by two
	}

	return pow_result;
}

long int _pow_modular(int a, int k, int r) {
	// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
	if (r == 1) { return 0; }

	mod_result = 1;
	a = a % r;
	while (k > 0) {
		if ((k & 1) > 0) {
			mod_result = (mod_result * a) % r;
		}

		k >>= 1;
		a = (a * a) % r;
	}

	return mod_result;
}

double _abs(double a) {
	if (a < 0) { return -a; }
	return a;
}
