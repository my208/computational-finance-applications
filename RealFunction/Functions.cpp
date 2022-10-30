#include "Functions.h"
#include <iostream>
#include <cmath>
#include <limits>

PolyFunction::PolyFunction(double a, double b, double c, double d) :a_(a), b_(b), c_(c), d_(d) {}

double PolyFunction::operator()(double x) const
{
	// a_ * std::pow(x, 5.0) + b_ * std::pow(x, 3.0) + c_ * x + d_
	return ((a_ * x * x + b_) * x * x + c_) * x + d_; // Horner's Rule
}

MixFunction::MixFunction(double a, double b, double c) :a_(a), b_(b), c_(c) {}

double MixFunction::operator()(double x) const
{
	double tol = 0.00001;
	static const double zero_ = std::sqrt(std::numeric_limits<double>::epsilon());
	if (std::abs(x - zero_) < tol)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	return (x * x + std::sin(a_ * x + b_)) / x + c_;
}

double secant(const RealFunction& obj, double x_i_minus_1, double x_i, double tol, int maxIter)
{
	for (int i = 0; i < maxIter; i++)
	{
		double fx_i_minus_1, fx_i, x_i_plus_1;
		fx_i_minus_1 = obj(x_i_minus_1);
		fx_i = obj(x_i);
		// secant method find root formula
		x_i_plus_1 = x_i - (fx_i * (x_i - x_i_minus_1) / (fx_i - fx_i_minus_1));

		if (std::abs(x_i_plus_1 - x_i) < tol)
		{
			return x_i_plus_1;
		}

		x_i_minus_1 = x_i;
		x_i = x_i_plus_1;
	}
	return std::numeric_limits<double>::quiet_NaN();
}


// test
int main()
{
	double tol = 0.00001;
	int maxIter = 1000;

	PolyFunction poly_test1(0.1, 0.25, -3, -1);
	MixFunction mix_test1(25, 5, -10);

	double result1, result2;
	result1 = secant(poly_test1, 2.0, 2.35, tol, maxIter);
	result2 = secant(mix_test1, 9.5, 10.5, tol, maxIter);
	
	std::cout << "poly root: " << result1 << std::endl;;
	std::cout << "mix root: " << result2 << std::endl;;

	return 0;
}