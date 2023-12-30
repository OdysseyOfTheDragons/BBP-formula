/**
 * @file
 * This file aims to provide a clear API for the client-server communications.
 * There is also a set of utilities that go with the API.
 *
 * All the communications are through strings, acting as keywords.
 */
#ifndef API
#define API
#include <stdbool.h>

/// Client asks the server which digit to calculate, and the number.
#define API_GET_POS "API_GET_POS"

/// Server tells the client the position of the first digit to calculate,
/// and the number of digits to compute.
///
/// The string is of the form `${API_CALC_DIGITS}[start]|[number]`.
#define API_CALC_DIGITS "API_START_WITH:"

/// The client tells the server to store the given HEX digits.
///
/// The string is of the form `${API_STORE}[start]|[number]|[digits]`.
#define API_STORE "API_STORE:"

/// The maximum length of any conversation.
#define API_LENGTH 16384

/// Get if the string starts with the `prefix`.
///
/// @param str The main string
/// @param prefix The prefix to check at the beginning of `str`
/// @return A boolean that indicates whether `str` starts with `prefix`
bool startswith(char *str, char *prefix);

/// Split the string given with the delimiter `|`.
///
/// 3 pointers to strings are asked, because at most, the string will be
/// divided into 3 parts: `start`, `number`, `digits`.
/// 
/// Set the third part (`part3`) to `NULL` if it is not needed.
/// Otherwise, a `Segmentation fault` will be raised.
///
/// @param str The string to split
/// @param prefix The prefix of the string (from the API)
/// @param part1 A pointer to the string that will accept the first part
/// @param part2 A pointer to the string that will accept the second part
/// @param part3 A pointer to the string that will accept the third part
void split(char *str, char *prefix, char **part1, char **part2, char **part3);
#endif
