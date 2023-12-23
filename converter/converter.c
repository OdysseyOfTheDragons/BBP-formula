/**
 * @file
 * The base **16** to base **10** converter.
 */

#include "converter.h"
#include "mathematics/mathematics.h"
#include "import.h"

char convert_digit(long double digit)
{
	const char hex[] = "0123456789ABCDEF";

	digit = _abs(digit);
	digit = 16.0 * (digit - _floor(digit));

	return hex[(int)digit];
}

/// Converts a single digit in base **16** back to the base **10**
/// with its integer value (\f$0\f$ to \f$15\f$).
///
/// @param digit The base **16** digit
/// @return The integer value of the digit in base **10**
char convert_back(char digit)
{
	if (digit >= '0' && digit <= '9') {
		return digit - '0';
	}
	return digit - 'A' + 10;
}

/// The number of digits after the comma.
/// The more, the better, but at the same time the required memory
/// and the computation duration will be higher.
#define PRECISION 33554432

/// The input base (here, we are in base **16**).
#define INPUT_BASE 16.0

/// The output base (base **10** in our case).
#define OUTPUT_BASE 10

/// The converted digits must be stored in a `.txt` file to be able to
/// return the `string` needed, as well as to keep a trace of the
/// computed digits. 
#define OUTPUT_FILE "build/out.txt"

char *convert(char *digits)
{
	printf("Starting converting pi to base 10:\n");

	// Holds the final pi number
	mpfr_t pi;

	// Holds the decimals from the division of 1 by powers of 16
	mpfr_t division;

	// Every digit in base 10
	mpfr_t dgt;

	// Initialisation
	mpfr_init2(pi, PRECISION);
	mpfr_init2(division, PRECISION);
	mpfr_init2(dgt, PRECISION);

	// Set first value
	mpfr_set_d(pi, 3.0, MPFR_RNDD);
	mpfr_set_d(division, 1.0, MPFR_RNDD);

	unsigned int length = strlen(digits);
	unsigned int i;

	for (i = 0; i < length; i++) {
		printf("\r> %d", i);

		// division = division / 16
		mpfr_div_ui(division, division, INPUT_BASE, MPFR_RNDD);

		// Get the decimal digit
		mpfr_set_d(dgt, convert_back(digits[i]), MPFR_RNDD);

		// digit = digit * division
		mpfr_mul(dgt, dgt, division, MPFR_RNDD);

		// pi = pi + digit
		mpfr_add(pi, pi, dgt, MPFR_RNDD);
	}
	printf("\n\n");

	FILE *f = fopen(OUTPUT_FILE, "w+");
	mpfr_out_str(f, OUTPUT_BASE, length, pi, MPFR_RNDD);
	fclose(f);

	f = fopen(OUTPUT_FILE, "r");
	char *str = (char *)malloc((length + 5) * sizeof(char));
	fscanf(f, "%s", str);
	fclose(f);

	// We get the string, without the extra e0 at the end
	str[length - 2] = '\0';

	mpfr_clear(pi);
	mpfr_clear(division);
	mpfr_clear(dgt);
	mpfr_free_cache();

	return str;
}
