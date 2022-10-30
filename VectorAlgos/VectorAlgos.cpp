#include "Quadratic.h"
#include "VectorAlgos.h"

#include <cmath>
using std::sqrt;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <algorithm>
using std::transform;
#include <numeric>
using std::accumulate;
using std::inner_product;
#include <utility>
#include <iostream>
using namespace std;

// constructor
VectorAlgos::VectorAlgos(vector<double>&& data, Quadratic&& quad) :data_(std::move(data)), quad_(std::move(quad))
{
	image_.resize(data_.size());
	runCalculations_();
}

map<CalcType, double> VectorAlgos::results() const
{
	return results_;
}

void VectorAlgos::resetCalc(vector<double>&& data, Quadratic&& quad)
{
	data_ = std::move(data);
	quad_ = std::move(quad);
	results_.clear();
	image_.resize(data_.size());
	runCalculations_();
}

void VectorAlgos::runCalculations_()
{
	transform(data_.begin(), data_.end(), image_.begin(), quad_);
	calcMeanAndStdDev_();
    calcNorm_();
    calcMaxAndMin_();
}

void VectorAlgos::calcMeanAndStdDev_()
{
	double mean = accumulate(image_.begin(), image_.end(), 0.0) / image_.size();

	auto sdElem = [mean](double x) -> double
	{
		return (x - mean) * (x - mean);
	};

	vector<double> sdElems(image_.size());
	transform(image_.begin(), image_.end(), sdElems.begin(), sdElem);

	double sd = sqrt(accumulate(sdElems.begin(), sdElems.end(), 0.0) / image_.size());

	results_.insert({CalcType::MEAN, mean});
	results_.insert({CalcType::STD_DEV, sd});
}

void VectorAlgos::calcNorm_()
{
	double norm = sqrt(inner_product(image_.begin(), image_.end(), image_.begin(), 0.0));
	results_.insert({CalcType::NORM, norm});
}

void VectorAlgos::calcMaxAndMin_()
{
	double max = *std::max_element(image_.begin(), image_.end());
	double min = *std::min_element(image_.begin(), image_.end());

	results_.insert({CalcType::MAX, max});
	results_.insert({CalcType::MIN, min});
}