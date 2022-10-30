#include "Shapes.h"
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::string;

Rectangle::Rectangle(double length, double height) :length_(length), height_(height),
	whatAmI_("Rectangle"){}

double Rectangle::operator()() const 
{
	return length_ * height_;
}

string Rectangle::whatAmI() const
{
	return whatAmI_;
}


Circle::Circle(double radius) :radius_(radius), pi_(3.14159265359),
	whatAmI_("Circle"){}

double Circle::operator()() const
{
	return pi_ * radius_ * radius_;
}

string Circle::whatAmI() const
{
	return whatAmI_;
}


ShapeShifter::ShapeShifter(std::unique_ptr<Shape> ss) :ss_(std::move(ss)) {}

double ShapeShifter::multiplier(double x)
{
	return x * ss_->operator()();
}
 
void shape_shifter_tests()
{
	auto unit_circle = std::make_unique<Circle>(1);
	auto two_by_four = std::make_unique<Rectangle>(2, 4);

	ShapeShifter circle_shift(std::move(unit_circle));
	ShapeShifter rect_shift(std::move(two_by_four));

	cout << "circle_shift(1.0) = " << circle_shift.multiplier(1.0) << endl;
	cout << "circle_shift(-2.5) = " << circle_shift.multiplier(-2.5) << endl;
	cout << "rect_shift(-2.0) = " << rect_shift.multiplier(-2.0) << endl;
	cout << "rect_shift(2.5) = " << rect_shift.multiplier(2.5) << endl;
}

int main()
{
	shape_shifter_tests();
	return 0;
}
