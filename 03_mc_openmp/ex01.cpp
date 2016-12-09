#include <omp.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout << "I am the " << omp_get_thread_num() << "\t"
	          << " the " << omp_get_num_threads() << std::endl;
	return 0;
}