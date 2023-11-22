#include "mathematics/mathematics.h"

long double _pow(int a, int k) {
	long double result = 1.0;
	long double base = a;

	if (k < 0) {
		base = 1.0 / a;
		k = -k;
	}

	while (k > 0) {
		if (k % 2 == 1) {
			result *= base;
			k--;
		}

		base *= base;
		k /= 2;
	}

	return result;
}

long int _pow_modular(int a, int k, int r) {
	// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
	if (r == 1) { return 0; }

	long int result = 1;
	a = a % r;
	while (k > 0) {
		if ((k & 1) > 0) {
			result = (result * a) % r;
		}

		k >>= 1;
		a = (a * a) % r;
	}

	return result;
}

double _abs(double a) {
	if (a < 0) { return -a; }
	return a;
}
