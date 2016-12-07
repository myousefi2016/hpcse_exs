#include "simpson.hpp"
#include <cmath>
#include <iostream>

double func(double x)
{
	return x * std::sin(x);
}

int main()
{
	double a;  //lower bound of integration
	double b;  //upper bound of integration
	unsigned int nsteps;  //number of subintervals

	// read the parameters
	std::cin >> a >> b >> nsteps;

	// print the result
	std::cout << simpson(func,a,b,nsteps)
	           << std::endl;
}