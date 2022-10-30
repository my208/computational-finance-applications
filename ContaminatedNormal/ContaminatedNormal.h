#ifndef CONTAMINATED_NORMAL_H
#define CONTAMINATED_NORMAL_H

#include <vector>

class ContaminatedNormal
{
public:
	ContaminatedNormal(double mean, double sd_one, double sd_two, 
		double alpha, int seed, int num_variates);

	double operator [](int k) const;
	int num_variates() const;

	void generate();
	void generate(double mean, double sd_one, double sd_two, double alpha, int seed, int num_variates);

private:
	void check_volatilities_() const;
	double mean_, sd_one_, sd_two_;
	double alpha_;
	int seed_, num_variates_;
	std::vector<double> cont_norm_variates_;
};

#endif

