#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <string>
#include <memory>

class Shape
{
public:	
	virtual double operator()() const = 0;		// Returns the area of the shape
	virtual std::string whatAmI() const = 0;	// std::string shape identifier
	virtual ~Shape() = default;					// Always implement virtual dtor on base class!
};

class Rectangle final : public Shape
{
public:
	Rectangle(double length, double height);
	virtual double operator()() const override;			// Area of the rectangle
	virtual std::string whatAmI() const override;		// Rectangle

private:
	double length_;
	double height_;
	std::string whatAmI_;
};

class Circle :public Shape
{
public:
	Circle(double radius);
	virtual double operator()() const override;			// Area of the circle
	virtual std::string whatAmI() const override;		// Circle

private:
	double radius_;
	double pi_;
	std::string whatAmI_;
};

class ShapeShifter
{
public:
	ShapeShifter(std::unique_ptr<Shape> ss);

	// Rule of Five:
	// Disable the copy constructor:
	ShapeShifter(const ShapeShifter& rhs) = delete;
	// Disable the copy assignment operator:
	ShapeShifter& operator = (const ShapeShifter& rhs) = delete;
	// Explicitly allow the default move constructor:
	ShapeShifter(ShapeShifter&& rhs) = default;
	// Explicitly allow the move assignment operator:
	ShapeShifter& operator = (ShapeShifter&& rhs) = default;
	// Explicitly declare the default destructor:
	~ShapeShifter() = default;

	double multiplier(double x);
 
private:
	std::unique_ptr<Shape> ss_;
};
 
void shape_shifter_tests();

#endif
