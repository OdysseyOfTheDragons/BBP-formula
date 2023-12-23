# BBP formula

Implementation of the [Bailey-Borwein-Plouffe formula](https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula) in `C`.

## Project idea

We are [two French students](Contributors.md), in [Lycée Hoche](https://en.wikipedia.org/wiki/Lyc%C3%A9e_Hoche) (Versailles), and we decided to test our limits. As we love the number \f$\pi\f$, we searched for a way to calculate its decimal digits.

Most of the existing algorithms require a powerful computer, with a lot of computational power, or memory.

We do not have that.

So here comes the Bailey-Borwein-Plouffe formula, which makes it possible, to only calculate a specific digit, without computing all of the previous ones.

## Commands

This project uses `make` commands to build and use the project.

As such, the following commands are usable:
* `calculator`: builds the calculator and test its speed to calculate the first \f$N\f$-th digits;
* `client`: builds the server client;
* `server`: buildis the server backend part;
* `clean`: deletes all build files;
* `tarball`: ouputs a tar archive with all the code;
* `format`: formats all `.c` and `.h` files following the Linux conventions;
* `docs`: builds this documentation.

## Project architecture

The project can be cut down in smaller modules. They are all inter-connected, but are built apart to sustain a more maintainable architecture.

### Calculator

This is the implementation of the BBP formula in C. This is where all the _magic_ takes place.

_Usage:_ you call the `pi()` function from `calculator/algorithm/algorithm.c`.

```c
#include <stdio.h>
#include <stdlib.h>

#include "calculator/algorithm.h"

int main() {
    printf("The 1000th digit in base 16 is %ld\n.", pi(1000));
    return EXIT_SUCCESS;
}
```

**Please note**: the algorithm returns the digit in base **16**. It is the role of the next module to convert it either to a base **16** string, or to the base **10**.

### Converter

Converts the digits between the **16** and **10** bases.

_Usage:_ you call the `convert_digit()` to get the base **16** `char` corresponding to the computed digit with the `pi()` function. You can then build a `char*` string to keep all the digits in base **16**, which will be useful later...
```c
#include <stdlib.h>

#include "converter/converter.h"
#include "calculator/algorithm.h"

int main() {
    unsigned int N = 10;

    // We add 1 to N because there will be the '\0' final character
    char *string = (char*)malloc((N + 1) * sizeof(char));

    for (unsigned int i = 0; i < N; i++) {
        string[i] = convert_digit(pi(i));
    }
    string[i] = '\0';

    // The string is now usable...

    free(string);
    return EXIT_SUCCESS;
}
```
