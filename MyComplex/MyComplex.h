#ifndef MYCOMPLEX_H
#define MYCOMPLEX_H
#include <iostream>
#include <cmath>

class MyComplex
{
   public:
       MyComplex(double x, double y); // constructor
       MyComplex();    // default constructor
 
       void print(); // member function that displays the complex number
 
       // accessor functions
       double real() const;
       double imag() const;
       double radius() const;
       double theta() const;
 
       void reset(double x, double y); // mutator function
  
       MyComplex operator+(const MyComplex& obj) const; // addition operator
 
 
   private:
	   // calculate polar coordinates of the complex number
       void calcPolar_();
 
	   // private members
       double real_;
       double imag_;
       double radius_;
       double theta_;
};
 
#endif
