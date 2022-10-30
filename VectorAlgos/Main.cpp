#include "Quadratic.h"
#include "VectorAlgos.h"

#include <vector>
using std::vector;
#include <numeric>
using std::iota;
#include <map>
using std::map;
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm> 
using std::for_each;
#include <utility>
using std::move;
using namespace std;

void testQuadraticAlgos();

int main()
{
	testQuadraticAlgos();
	return 0;
}

void testQuadraticAlgos()
{
	// create instance of Quadratic class, vectors of x values
	Quadratic qd1(-2.0, -4.0, 2.0), qd2(-2.0, -4.0, 2.0);
	vector<double> data1(15), data2(15);
	iota(data1.begin(), data1.end(), -10.0);
	iota(data2.begin(), data2.end(), 0.75);

	// create instance of VectorAlgos class, store results in STL map res1
	VectorAlgos valgo(move(data1), move(qd1));
	map<CalcType, double> res1 = valgo.results();

	// reset for res2
	valgo.resetCalc(move(data2), move(qd2));
	map<CalcType, double> res2 = valgo.results();

	// lambda expression display_results
    auto display_results = [](std::pair<CalcType,double> elem)
	{
		cout << static_cast<unsigned>(elem.first) << ": result = " << elem.second << endl; 
	};
	
	// display the results in res1 using an iterator
	for (const auto& elem : res1)
	{
		display_results(elem);
	}
	cout << endl; 

	// display the results in res2 using an iterator
	for (const auto& elem : res2)
	{
		display_results(elem);
	}
}