#ifndef MATHEMATICS
#define MATHEMATICS
/// All the mathematics utils for the project

/// Calculates `a` to the power of `k` with a good complexity
///
/// @param a The base
/// @param k The power
/// @return a ** k
long double _pow(int a, int k);

/// Calculates `a` to the power of `k` modulo `r`
///
/// @param a The base
/// @param k The power
/// @param r The modulo
/// @return (a ** k) mod r
long int _pow_modular(int a, int k, int r);

/// Calculates the absolute value of `a`
///
/// @param a The value
/// @return |a|
double _abs(double a);
#endif
