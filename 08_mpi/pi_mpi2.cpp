#include <iostream>
#include <iomanip>      // std::setprecision
#include <mpi.h>
#include <timer.hpp>

int main(int argc, char *argv[])
{
	timer t;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	unsigned long const nterms = 100000000;
	long double const step = (double)(nterms)/size;
	unsigned long start = rank*step;
	unsigned long end = (rank + 1)*step;
	long double sum = 0;
	long double localsum = 0;

	t.start();

	for(std::size_t t = start; t < end; t++) {
		localsum += (1.0 - 2*(t % 2)) / (2*t + 1);
	}
	// collect result
	MPI_Reduce(&localsum, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	t.stop();
	if(rank==0) {
  		std::cout << "Timing : " << t.get_timing() << std::endl;
		std::cout<<"pi = "<< std::setprecision(18) <<4*sum<<std::endl;
	}
	MPI_Finalize();
	return 0;
}