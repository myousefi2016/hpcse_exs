#include <mpi.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	double a = 0;
	double b = 4;
	double dx = 0.001;
	double ts = 0;
	double te = 10;
	double dt = 0.001;
	int nt = (te - ts)/dt;
	int nx = (b - a)/dx;
	
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int rank;
	int size;
	MPI_Comm_rank(&rank);
	MPI_Comm_size(&size);

	if(rank % 2 ==0) {
		MPI_Send(&density[1])
	}
	return 0;
}