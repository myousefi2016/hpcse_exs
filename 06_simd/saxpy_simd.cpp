#include <x86intrin.h>
#include <iostream>
#include <cassert>
#include "timer.hpp"

void saxpy_simd(int n, float a, float* x, float* y)
{
	// load the scale factor four time into a register
	__m128 x0 = _mm_set1_ps(a);

	// we assume alignment
	assert(((std::size_t)x) % 16 ==0 && ((std::size_t)y) % 16 ==0);

	int ndiv4 = n/4;

	// loop over chunks of 4 values
	for(int i=0; i<ndiv4; ++i) {
		__m128 x1 = _mm_load_ps(x+4*i); // aligned (fast) load
		__m128 x2 = _mm_load_ps(y+4*i); // aligned (fast) load
		__m128 x3 = _mm_mul_ps(x0, x1); // aligned (fast) load
		__m128 x4 = _mm_add_ps(x2, x3); // aligned (fast) load
		_mm_store_ps(y+4*i, x4);
	}

	// do the remaining entries
	for(int i=ndiv4*4; i<n; ++i)
		y[i] += a*x[i];

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
	saxpy_simd(n, 2.0, x, y);
	t.stop();


	std::cout << "Time: " << t.get_timing() << std::endl;

	return 0;
}