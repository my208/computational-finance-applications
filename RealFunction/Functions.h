#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <cmath>
#include <limits>

class RealFunction
{
public:
	virtual double operator()(double x) const = 0;
	virtual ~RealFunction() = default;
};

class PolyFunction: public RealFunction
{
public:
	PolyFunction(double a, double b, double c, double d);
	virtual double operator()(double x) const override;

private:
	double a_, b_, c_, d_;
};

class MixFunction: public RealFunction
{
public:
	MixFunction(double a, double b, double c);
	virtual double operator()(double x) const override;

private:
	double a_, b_, c_;
};

double secant(const RealFunction& obj, double x_i_minus_1, double x_i, double tol, int maxIter);

#endif