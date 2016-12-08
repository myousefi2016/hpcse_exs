// Example codes for HPC course
// (c) 2012 Matthias Troyer, ETH Zurich

#include <vector>
#include <iostream>
#include <thread>
#include <numeric>
#include <iomanip>
#include <timer.hpp>

// sum terms [i-j) of the power series for pi/4
void sumterms(long double& sum, std::size_t i, std::size_t j)
{
  sum = 0.0;
  
  for (std::size_t t = i; t < j; ++t)
    sum += (1.0 - 2* (t % 2)) / (2*t + 1);
}


int main()
{
  // decide how many threads to use

  unsigned long const nterms = 100000000;
  
  long double result = 0;
  timer time;
  time.start();
  sumterms(result, 0, nterms);
  time.stop();
  
  // print the result
  std::cout << "time: " << time.get_timing() << "\t" 
            << "pi = " << std::setprecision(18) << 4*result << std::endl;
  return 0;
}
