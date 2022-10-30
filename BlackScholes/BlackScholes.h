#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#include <iostream>
#include <cmath>
#include <array>

// enum class
enum class PayoffType
{
	CALL = 1, // 1
	PUT = -1 // -1
};

// declare functions & variables
double norm_cdf(double x);
std::array<double, 2> dee_fcns(double strike, double spot, double rate, double sigma, double year_frac);
double black_scholes_price(double strike, double spot, double rate, double sigma, double year_frac, PayoffType pot);
using OptionData = std::array<double, 5>;
double black_scholes_price(const OptionData& OptionData, PayoffType pot);

#endif

