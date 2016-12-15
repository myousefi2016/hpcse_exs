// Example codes for HPC course
// (c) 2016 Panos Hadjidoukas, ETH Zurich

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	const int nlocal = 10;
	double data[nlocal];

	for (int i = 0; i < nlocal; i++) data[i] = 100*rank + i;

	int step = 0;
	char filename[256];

	sprintf(filename, "bin_%05d.bin", step);

	MPI_File f;
	MPI_File_open(MPI_COMM_WORLD, filename , MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &f);

	MPI_File_set_size (f, 0);

	MPI_Offset base;
	MPI_File_get_position(f, &base);

	MPI_Offset len = nlocal*sizeof(double);
	MPI_Offset offset = rank*len;
	MPI_Status status;

	MPI_File_write_at_all(f, base + offset, data, nlocal, MPI_DOUBLE, &status);

	MPI_File_close(&f);

	MPI_Finalize();
}
