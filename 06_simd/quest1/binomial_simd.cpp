#include <iostream>
#include <x86intrin.h>
#include "timer.hpp"

void square_binomial(int n, float* x, float* y, float* z)
{
    //
    __m128 a = _mm_set1_ps(2.0); // 
    int ndiv4 = n/4;
    for(int i=0; i<ndiv4; ++i)
    {
        __m128 x0 = _mm_load_ps(x+4*i); // load
        __m128 x1 = _mm_load_ps(y+4*i); // load
        __m128 x2 = _mm_load_ps(z+4*i); // load
        __m128 x3 = _mm_mul_ps(x0, x0); // mul
        __m128 x4 = _mm_mul_ps(x1, x1); // mul
        __m128 x5 = _mm_mul_ps(x0, x1); // mul
        __m128 x6 = _mm_mul_ps(a, x1); // mul
        __m128 x7 = _mm_add_ps(x3, x4); // add
        __m128 x8 = _mm_add_ps(x7, x6); // add
        _mm_store_ps(z+4*i, x8);
    }

    //
    for(int i=ndiv4*4; i<n; ++i)
    {
        z[i] = x[i]*x[i] + y[i]*y[i] + 2*x[i]*y[i];
    }

}

int main(int argc, char const *argv[])
{
    //
    timer t;
    int n = 10000;

    float x[n];
    float y[n];
    float z[n];
    for(int i=0; i<n; i++) {
        x[i] = 1;
        y[i] = 2;
    }
    
    t.start();
    square_binomial(n, x, y, z);
    t.stop();


    std::cout << "Time: " << t.get_timing() << std::endl;
    return 0;
}