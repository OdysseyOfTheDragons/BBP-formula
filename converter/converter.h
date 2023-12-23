#ifndef CONVERTER
#define CONVERTER
/// Converts a double digit in base **10** to its equivalent
/// in base **16** (`'0'` to `'F'`).
///
/// @param digit The computed digit
/// @return The equivalent character to the given digit
char convert_digit(long double digit);

/// Converts a whole string of digits (without the integer part) in
/// base **16** to the same string in base **10**.
///
/// @param digits The whole string with the base **16** digits
/// @returns The same string but with the base **10** digits
char *convert(char *digits);
#endif
