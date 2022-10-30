#include "BlackScholes.h"
#include <iostream>
#include <cmath>
#include <array>
using std::array;

// normal CDF
double sqrt_two = std::sqrt(2);

double norm_cdf(double x)
{
	return (1 - erf(-x / sqrt_two)) / 2;
}

// d1 d2
std::array<double, 2> dee_fcns(double strike, double spot, double rate, double sigma, double year_frac)
{
	std::array<double, 2> d;

	d[0] = (std::log(spot / strike) + (rate + sigma * sigma / 2) * year_frac) / (sigma * std::sqrt(year_frac));
	d[1] = d[0] - sigma * std::sqrt(year_frac);

	return d;
}

// black_scholes_price(.) function
double black_scholes_price(double strike, double spot, double rate, double sigma, double year_frac, PayoffType pot)
{		
	if(strike <= 0.0 || spot <= 0.0 || sigma <= 0.0)
	{
		return std::nan("");
	}

	if(year_frac == 0.0)
	{
		return std::max((int) pot * (spot - strike), 0.0);
	}

	double result;
	result = (int) pot * (spot * norm_cdf((int) pot * dee_fcns(strike, spot, rate, sigma, year_frac)[0]) 
	- strike * std::exp(-rate * year_frac) * norm_cdf((int) pot * dee_fcns(strike, spot, rate, sigma, year_frac)[1])) ;
	
	return result;
}


// overload black_scholes_price(.) function
double black_scholes_price(const OptionData& OptionData, PayoffType pot)
{
	return black_scholes_price(OptionData[0], OptionData[1], OptionData[2], OptionData[3], OptionData[4], pot);
}


// test
int main()
{
	double y;
	y = norm_cdf(0.3);
	std::cout << "norm_cdf = " << y << std::endl;

	double strike = 100;
	double spot = 108;
	double rate = 0.05;
	double sigma = 0.2;
	double year_frac = 1;
	PayoffType pot = PayoffType::CALL;
	
	double z;
	z = black_scholes_price(strike, spot, rate, sigma, year_frac, pot);
	std::cout << "BS price = " << z << std::endl;

	std::array<double, 5> OptionData = {100.0, 108.0, 0.05, 0.2, 1.0};
	double z2;
	z2 = black_scholes_price(OptionData, pot);
	std::cout << "overload BS price = " << z2 << std::endl;

	return 0;
}
