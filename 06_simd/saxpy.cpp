#include <x86intrin.h>
#include <iostream>
#include <cassert>
#include "timer.hpp"

void saxpy(int n, float a, float* x, float* y)
{
	// loop over chunks of 4 values
	for(int i=0; i<n; ++i) {
		y[i] = y[i] + a*x[i];
	}
}

int main(int argc, char const *argv[])
{
	timer t;
	int n = 1000000000;

	float x[n];
	float y[n];
	for(int i=0; i<n; i++) {
		x[i] = i;
		y[i] = i;
	}

	t.start();
	saxpy(n, 2.0, x, y);
	t.stop();
	std::cout << "Time: " << t.get_timing() << std::endl;
	// for(int i=0; i < n; i++) {
	// 	std::cout << y[i] << std::endl;
	// }
	return 0;
}