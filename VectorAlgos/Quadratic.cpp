#include "Quadratic.h"

Quadratic::Quadratic(double a, double b, double c) :a_(a), b_(b), c_(c)
{

}

double Quadratic::operator()(double x)  const
{
	return (a_ * x + b_) * x + c_;
}


