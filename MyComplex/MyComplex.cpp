#include "MyComplex.h"
#include <iostream>
#include <cmath>
 
// constructor
MyComplex::MyComplex(double x, double y) :real_(x), imag_(y)
{
   calcPolar_();
}
 
// default constructor
MyComplex::MyComplex() :real_(0), imag_(0), radius_(0), theta_(0){}

// print() function that displays the complex number to the screen
void MyComplex::print()
{
	std::string plus_or_minus;

	if (imag_ >= 0)
	{
		plus_or_minus = " + ";
	}
	else
	{
		plus_or_minus = " - ";
	}

	std::cout << real_ << plus_or_minus << std::abs(imag_) << "i" << std::endl;
}

// accessor functions
double MyComplex::real() const
{
   return real_;
}
 
double MyComplex::imag() const
{
   return imag_;
}
 
double MyComplex::radius() const
{
   return radius_;
}
 
double MyComplex::theta() const
{
   return theta_;
}

// mutator function reset()
void MyComplex::reset(double x, double y)
{
   real_ = x;
   imag_ = y;
   calcPolar_();
}

// addition operator
MyComplex MyComplex::operator+(const MyComplex& obj) const
{
   MyComplex temp(real_ + obj.real_, imag_ + obj.imag_);
   return temp;
}

// calculate and set the corresponding polar coordinates
void MyComplex::calcPolar_()
{  
   radius_ = std::sqrt(real_ * real_ + imag_ * imag_);

   if (real_ == 0 && imag_ == 0)
   {
		theta_ = 0;
		return;
   }

   double theta_temp = std::acos(real_ / radius_);

   if (imag_ >= 0)
   {
		theta_ = theta_temp;
   } 
   else
   {
		theta_ = - theta_temp;
   }
}

// test
int main()
{
   MyComplex c1(3, 4), c2(-2, -3), c3(0, 0);
   MyComplex c4 = c1 + c2 + c3;
   MyComplex c5; // call default
   
   MyComplex test = c4;
   test.print();
   std::cout << "radius: " << test.radius() << std::endl;;
   std::cout << "theta: " << test.theta() << std::endl;;

   return 0;
}
