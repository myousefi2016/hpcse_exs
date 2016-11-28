#include <iostream>
#include <x86intrin.h>
#include "timer.hpp"

void square_binomial(int n, float* x, float* y, float* z)
{
    //
    for(int i=0; i<n; ++i)
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