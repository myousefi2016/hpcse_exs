#include <omp.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	#pragma omp parallel for ordered
	for(int i=0; i<100; ++i)
	{
		#pragma omp ordered
		std::cout << "i = " << i << std::endl;
	}
	return 0;
}