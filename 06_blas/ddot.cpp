#include <iostream>
#include <cblas.h>
#include <vector>

extern "C" double ddot_(int& n, double* x, int& incx, double* y, int& incy);
int main(int argc, char const *argv[])
{
	std::vector<double> x(10, 1);
	std::vector<double> y(10, 2);

	// calculate the inner product
	int n=x.size();
	int one = 1;
	double d = ddot_(n, &x[0], one, &y[0], one);
	std::cout << d << std::endl; // should be 20
	return 0;
}