#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{
	double xs = 0;
	double xe = 4;
	double dx = 0.001;

	double ts = 0;
	double te = 10;
	double dt = 0.001;

	int nt = (te - ts)/dt;
	int nx = (b - a)/dx;

	double density[nx];
	// initialize the density
	for(i=0; i<nx; i++) {
		density[i] = std::sin(xs + i*dx)
	}

	for(i=0; i < nt; i++) {
		for(j=1; j < nx - 1; j++) {
			density[j] = (density[j+1] + density[j-1] - 2*density[i])/dx/dx*dt 
			             + density[i]
		}
		density[0] = (density[2] + density[0] - 2*density[1])/dx/dx*dt 
			             + density[0]
		density[nx - 1] = (density[nx - 1] + density[nx - 3] - 2*density[nx - 2])/dx/dx*dt 
			             + density[nx - 1]
	}


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