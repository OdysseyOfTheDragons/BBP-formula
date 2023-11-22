#include "algorithm/algorithm.h"
#include "mathematics/mathematics.h"

/// Calulates the Sn term of the Nth decimal with the value `a`
///
/// @param N The place of the decimal to calculate
/// @param a A precise parameter
/// @return The sum desired
long double sn(int N, int a) {
	long double sum = 0;

	// To be faster, the variables are declared before use
	int k;
	long double eight;
	long double numerator;
	long double coeff;

	for (k = 0; k <= N - 1; k++) {
		eight = 8 * k + a;
		numerator = _pow_modular(16, N - k, eight);
		
		coeff = numerator / eight;
		sum += coeff - (int)coeff;
		sum -= (int)sum;
	}

	long double cache = 0.0;
	while (1) {
		numerator = _pow(16, N - k);
		eight = 8 * k + a;

		coeff = numerator / eight;
		if (cache == coeff) { // || coeff < PRECISION) {
			break;
		}

		cache = coeff;
		sum += coeff - (int)coeff;
		sum -= (int)sum;
	}

	return sum;
}

long double pi(int N) {
	long double sn_1 = sn(N, 1);
	long double sn_4 = sn(N, 4);
	long double sn_5 = sn(N, 5);
	long double sn_6 = sn(N, 6);

	long double sum = 4 * sn_1 - 2 * sn_4 - sn_5 - sn_6;

	return sum - (int)sum + 1.0;
}
