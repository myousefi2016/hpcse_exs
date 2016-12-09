// Example codes for HPC course
// (c) 2012 Matthias Troyer, ETH Zurich

#include "simpson.hpp"
#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>
#include <numeric>
#include <iomanip>
#include <timer.hpp>


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

  double result=0;

  timer time;
  time.start();
  #pragma omp parallel
  {
    int num = omp_get_num_threads();
    int i = omp_get_thread_num();
    double begin, end;
    double delta = (b - a)/num;
    begin = a + i*delta;
    end = a + (i+1)*delta;
    double r = simpson(func,begin, end, nsteps/num);
    #pragma omp critical(simpsonresult)
    {
      result += r;
    }
  }
  time.stop();

  
  // print the result
  std::cout << "time: " << time.get_timing() << "\t" 
            << std::setprecision(18) << result << std::endl;
  
  return 0;
}