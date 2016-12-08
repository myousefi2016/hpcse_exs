// Example codes for HPC course
// (c) 2012 Matthias Troyer, ETH Zurich

#include "simpson.hpp"
#include <cmath>
#include <iostream>
#include <timer.hpp>
#include <iomanip>

// The function to integrate
double func(double x)
{
  return x * std::sin(x);
}


int main()
{
  double a;            // lower bound of integration
  double b;            // upper bound of integration
  unsigned int nsteps; // number of subintervals for integration
  
  // read the parameters
  std::cout << "Please input a, b, nsteps:" << std::endl;
  std::cin >> a >> b >> nsteps;
  
  // print the result
  timer time;
  time.start();
  double result = simpson(func,a,b,nsteps);
  time.stop();

  // print the result
  std::cout << "time: " << time.get_timing() << "\t" 
            << std::setprecision(18) << result << std::endl;
  
  return 0;
}