/**
 * @file
 * Manipulates the data.
 */
#ifndef DATABASE
#define DATABASE
/// Output directory to the files.
#define DATABASE_OUTPUT "database/data"

/// Next position of the digit to calculate.
#define DATABASE_POSITION "database/data/database_position.txt"

/// The list of files with all the hex digits inside.
#define DATABASE_HEX_LIST "database/data/database_hex_list.txt"

/// Initializes the database.
///
/// This function must be called every time the server starts.
/// Use this function to ensure the database files exist, and are valid.
///
/// @return The starting digit to compute
unsigned long int database_init();

/// Get the starting digit to compute.
///
/// @return The starting digit the client must compute
int database_get();

/// Update the starting digit to compute.
///
/// @param start The position of the next digit to compute
void database_update(int start);

/// Save a span of hex digits.
///
/// @param start The starting digits
/// @param number The number of digits computed
/// @param digits The HEX digits
void database_store_hex(int start, int number, char *digits);
#endif
