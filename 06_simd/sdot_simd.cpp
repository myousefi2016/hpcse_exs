#include <x86intrin.h>
#include <iostream>
#include <cassert>
#include "timer.hpp"

float sdot_simd(int n, float* x, float* y)
{
	// set the total sum to 0, one sum per vector element.
	__m128 x0 = _mm_set1_ps(0.);

	// we assume alignment
	assert((std::size_t)x % 16 ==0 && (std::size_t)x % 16 ==0);

	int ndiv4 = n/4;
	for(int i=0; i<ndiv4; ++i)
	{
		__m128 x1 = _mm_load_ps(x+i*4); 
		__m128 x2 = _mm_load_ps(y+i*4); 
		__m128 x3 = _mm_mul_ps(x1, x2);
		x0 = _mm_add_ps(x0, x3); // add x3 to x0 
	}

	//store the 4 partial sums back to aligned memory
	float aligns(16), tmp[4];
	_mm_store_ps(tmp, x0);

	// do the reduction over the vector elements by hand
	float sum = tmp[0] + tmp[1] + tmp[2] + tmp[3];

	// do the remaining enetries
	for (int i = ndiv4*4; i<n; ++i)
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
	float sum = sdot_simd(n, x, y);
	t.stop();


	std::cout << "Dot is: " << sum << std::endl
	          << "Time: " << t.get_timing() << std::endl;

	return 0;
}