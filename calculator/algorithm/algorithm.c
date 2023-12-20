#include "algorithm/algorithm.h"
#include "mathematics/mathematics.h"

#define PRECISION 1.0e-17

// To be faster, the variables are declared before use
// In sn()
long double sum;
int k;
long double eight;
long double numerator;
long double coeff;
long double cache;
// In pi()
long double sn_1;
long double sn_4;
long double sn_5;
long double sn_6;
long double total;

/// Calulates the Sn term of the Nth decimal with the value `a`
///
/// @param N The place of the decimal to calculate
/// @param a A precise parameter
/// @return The sum desired
long double sn(int N, int a) {
	sum = 0;
	cache = 0.0;

	// It would be closer to the formula to write k <= N - 1
	// but this would add an operation per iteration

	/* for (k = 0; k < N; k++) {
		eight = 8 * k + a;
		numerator = _pow_modular(16, N - k, eight);
		
		coeff = numerator / eight;
		sum += coeff - (int)coeff;
		sum -= (int)sum;
	} */

	// This should be faster
	for (k = 0; k < N; k++) {
		eight = 8 * k + a;
		numerator = _pow_modular(16, N - k, eight);
		
		coeff = numerator / eight;
		sum += coeff - (int)coeff;
		sum -= (int)sum;
	}

	while (1) {
		// numerator = _pow(16, N - k);
		// eight = 8 * k + a;

		coeff = _pow(16, N - k) / (8 * k + a);
		if (cache == coeff || coeff < PRECISION) {
			break;
		}

		cache = coeff;
		sum += coeff - (int)coeff;
		sum -= (int)sum;

		k++;
	}

	return sum;
}

long double pi(int N) {
	sn_1 = sn(N, 1);
	sn_4 = sn(N, 4);
	sn_5 = sn(N, 5);
	sn_6 = sn(N, 6);

	total = 4 * sn_1 - 2 * sn_4 - sn_5 - sn_6;

	return total - (int)total + 1.0;
}
