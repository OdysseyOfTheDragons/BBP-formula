#include "mathematics/mathematics.h"
#include "algorithm/algorithm.h"

#define N 10000

// #include <stdio.h>
// #include <math.h>
// #include <time.h>
// #include <stdlib.h>

// char hex[100];

/* void to_hex(double x, char chx[]) {
    double y;
    int i;
    const char hx[] = "0123456789ABCDEF";

    y = _abs(x);
    for (i = 0; i < 16; i++) {
        y = 16.0 * (y - floor(y));
        chx[i] = hx[(int)(y)];
    }
} */

int main(void) {
	// printf("Start with %d decimals\n", N);

	// pi(N);

	// clock_t t0 = clock();
	for (int i = 0; i < N; i++) {
		pi(i);

		// long double pi_n = pi(i);
		// to_hex(pi_n, hex);
		// printf("> i: %d | pi: %c\n", i, hex[0]);
	}
	// clock_t t1 = clock();

	// printf("\nTIME: %f seconds\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

	return 0;
}
