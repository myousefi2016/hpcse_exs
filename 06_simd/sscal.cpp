#include <iostream>
#include <x86intrin.h>

void sscal(int n, float a, float* x)
{
	// load the scale factor four times into a register
	__m128 x0 = _mm_set1_ps(a);

	int ndiv4 = n/4;
	// loop over chunks of 4 values

	for (int i=0; i<ndiv4; ++i) {
		__m128 x1 = _mm_load_ps(x+4*i); //aligned (fast) load
		__m128 x2 = _mm_mul_ps(x0, x1); //multiply
		_mm_store_ps(x+4*i, x2);
	}

	for (int i=ndiv4*4; i < n; ++i) {
		x[i] *= a;
	}

	// do the remaining entries
	int i = ndiv4*4;
	switch (n-i) {
		case 3: x[i+2] *= a;
		case 2: x[i+1] *=a;
		case 1: x[i] *= a;
	}
}