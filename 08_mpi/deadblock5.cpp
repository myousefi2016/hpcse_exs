#include <mpi.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double ds = 3.1415927; //to send
	double dr;             //to receive
	int tag = 99;

	if(rank==0) {
		MPI_Send(&ds, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&dr, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
	}
	else(rank==1) {
		MPI_Send(&ds, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
		MPI_Recv(&dr, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}