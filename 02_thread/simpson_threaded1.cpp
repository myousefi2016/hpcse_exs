#include "simpson.hpp"
#include <cmath>
#include <iostream>
#include <thread>

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

    double result1;  // the integral of the first half

    //spawn a thread for the first half of the interval
    std::thread t( [&] () 
    	{ 
    		result1 = simpson(func,a,a+(b-a)/2.,nsteps/2);
    	});
    // locally integrate the second half
    double result2 = simpson(func,a+(b-a)/2.,b,nsteps/2);
	
	t.join(); // wait for the thread to join
	// print the result
	std::cout << result1 + result2
	           << std::endl;
}