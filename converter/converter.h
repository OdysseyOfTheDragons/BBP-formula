#ifndef CONVERTER
#define CONVERTER
typedef struct String string;
unsigned int string_length(string* str);
char* string_content(string* str);

string* convert(char* digits);
#endif
