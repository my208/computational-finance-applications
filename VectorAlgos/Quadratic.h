#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <map>
#include <vector>

class Quadratic
{
public:
	Quadratic(double a, double b, double c);
	double operator()(double x) const;

private:
	double a_;
	double b_;
	double c_;
};

#endif