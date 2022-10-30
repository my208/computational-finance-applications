#include "ContaminatedNormal.h"
 
#include <random>
#include <iostream>
#include <vector>
#include <exception>
 
using std::mt19937_64;
using std::normal_distribution;
using std::vector;
using std::exception;
using std::cout;
using std::endl;
 
// constructor
ContaminatedNormal::ContaminatedNormal(double mean, double sd_one, double sd_two,
	double alpha, int seed, int num_variates) :mean_(mean), sd_one_(sd_one),
	sd_two_(sd_two), alpha_(alpha), seed_(seed), num_variates_(num_variates)
{
	check_volatilities_();
}
 
double ContaminatedNormal::operator [](int k) const
{
	if (k < 0) 
	{
		exception e("Exception: Negative index");
		cout << e.what() << endl;
		throw e;
	}
	if (k >= num_variates_) 
	{
		exception e("Exception: Index out of bounds");
		cout << e.what() << endl;
		throw e;
	}
	return cont_norm_variates_[k];
}
 
int ContaminatedNormal::num_variates() const
{
	return cont_norm_variates_.size();
}
 
void ContaminatedNormal::generate()
{
	// create engine
	mt19937_64 mtre(seed_);
	// create contaminated normal distribution object
	normal_distribution<> cnd(mean_, sd_one_);
	// create 2nd engine and generate numbers in same way
	mt19937_64 mtre2(seed_);
	// create contaminated normal distribution object
	normal_distribution<> cnd2(mean_, sd_two_);

	for (int i = 0; i < num_variates_; ++i)
	{
		cont_norm_variates_.push_back((1 - alpha_) * cnd(mtre) + alpha_ * cnd2(mtre2));
	}
}
 
void ContaminatedNormal::generate(double mean, double sd_one, double sd_two, double alpha, int seed, int num_variates)
{
	cont_norm_variates_.clear();
	mean_ = mean;
	sd_one_ = sd_one;
	sd_two_ = sd_two;
	alpha_ = alpha;
	seed_ = seed;
	num_variates_ = num_variates;
	check_volatilities_();
	generate();
}

void ContaminatedNormal::check_volatilities_() const
{
	if (sd_one_ <= 0 || sd_two_ <= 0)
	{
		exception e("Exception: Non-positive volatility, sd should be greater than 0.");
		cout << e.what() << endl;
		throw e;
	}
	if (sd_one_ >= sd_two_)
	{
		exception e("Exception: Inequality of the volatilities fails, sd_one_ should be less than sd_two_.");
		cout << e.what() << endl;
		throw e;
	}
}

// test
int main() 
{
	ContaminatedNormal temp(100, 10, 50, 0.5, 5, 5);
	temp.generate(100, -1, 0, 0.5, 5, 5);
	cout << temp.num_variates() << endl;
	for (int i = 0; i < temp.num_variates(); i++) {
		cout << temp[i] << endl;
	}
}