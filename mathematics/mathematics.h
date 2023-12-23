#ifndef MATHEMATICS
#define MATHEMATICS
/// Calculates `a` to the power of `k` with a good complexity.
///
/// @param a The base
/// @param k The power
/// @return \f$a^k\f$
long double _pow(int a, int k);

/// Calculates `a` to the power of `k` modulo `r`.
///
/// @param a The base
/// @param k The power
/// @param r The modulo
/// @return \f$a^k \mod r\f$
long int _pow_modular(int a, int k, int r);

/// Calculates the absolute value of `a`.
///
/// @param a The value
/// @return \f$|a|\f$
double _abs(double a);

/// Floors `val`.
///
/// @param val The value to floor
/// @return \f$\lfloor \text{val} \rfloor\f$
int _floor(long double val);
#endif
