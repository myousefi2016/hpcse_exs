#include <x86intrin.h>
#include <iostream>
#include <cassert>
#include "timer.hpp"

float sdot(int n, float* x, float* y)
{
	float sum = 0;
	for (int i = 0; i<n; ++i)
	{
		sum += x[i]*y[i];
	}

	return sum;

}

int main(int argc, char const *argv[])
{
	timer t;
	int n = 1000000000;

	float x[n];
	float y[n];
	for(int i=0; i<n; i++) {
		x[i] = 1;
		y[i] = 2;
	}
	
	t.start();
	float sum = sdot(n, x, y);
	t.stop();


	std::cout << "Dot is: " << sum << std::endl
	          << "Time: " << t.get_timing() << std::endl;

	return 0;
}