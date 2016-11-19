#include <mpi.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int rank;
	MPI_Comm_rank(&rank);

	if(rank % 2 ==0) {
		MPI_Send(&density[1])
	}
	return 0;
}