#include "converter.h"
#include <stdlib.h>

struct String {
	unsigned int length;
	char* content;
}

unsigned int string_length(string* str) {
	return str->length;
}


