#include <mpi.h>
#include <iostream>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0){
		int x = 33;
		MPI_Send(&x, 1, MPI_INT, 1, 123, MPI_COMM_WORLD);
	}
	if(rank==1){
		int y;
		MPI_Recv(&y, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
		std::cout << "Recieved " << y << "\n"
		          << "plus 1 equal" << y + 1 <<"\n";
	}
	MPI_Finalize();
	return 0;
}
