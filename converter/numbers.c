#include "import.h"

#define PRECISION 16777216
#define BASE 10
#define FILENAME "out.txt"
#define LENGTH 29

int main() {
	char str[] = {2, 4, 3, 15, 6, 10, 8, 8, 8, 5, 10, 3, 0, 8, 13, 3, 1, 3, 1, 9, 8, 10, 2, 14, 0, 3, 7, 0, 7};

	unsigned int i;
	mpfr_t pi, sixteen, add, result;

	mpfr_init2(pi, PRECISION);
	mpfr_init2(sixteen, PRECISION);
	mpfr_init2(add, PRECISION);
	mpfr_init2(result, PRECISION);

	mpfr_set_d(pi, 3.0, MPFR_RNDD);
	mpfr_set_d(sixteen, 16.0, MPFR_RNDD);
	mpfr_set_d(add, 0.0, MPFR_RNDD);
	mpfr_set_d(result, 1.0, MPFR_RNDD);

	for (i = 0; i < LENGTH; i++) {
		mpfr_div(result, result, sixteen, MPFR_RNDD);

		mpfr_t digit;
		mpfr_init2(digit, PRECISION);
		mpfr_set_d(digit, str[i], MPFR_RNDD);

		mpfr_mul(digit, digit, result, MPFR_RNDD);
		mpfr_add(pi, pi, digit, MPFR_RNDD);
	}

	FILE* f = fopen(FILENAME, "w");
	mpfr_out_str(f, BASE, LENGTH, pi, MPFR_RNDD);
	fclose(f);

	mpfr_clear(pi);
	mpfr_clear(sixteen);
	mpfr_clear(add);
	mpfr_clear(result);
	mpfr_free_cache();

	return EXIT_SUCCESS;
}
