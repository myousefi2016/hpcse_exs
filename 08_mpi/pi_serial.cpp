#include <iostream>
#include <iomanip>      // std::setprecision
#include <timer.hpp>

int main(int argc, char const *argv[])
{
	timer t;
	unsigned long const nterms = 100000000;
	long double sum = 0;

	t.start();

	for(int t = 0; t < nterms; t++) {
		sum += (1.0 - 2*(t % 2)) / (2*t + 1);
	}
	t.stop();
    std::cout << "Timing : " << t.get_timing() << std::endl;
	std::cout<<"pi = "<< std::setprecision(18) <<4*sum<<std::endl;
	return 0;
}