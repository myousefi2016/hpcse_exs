#include <mpi.h>
#include <iostream>
#include <cmath>
#include <fstream>

int main(int argc, char const *argv[])
{
	double xs = 0;
	double xe = 4;
	double dx = 0.001;

	double ts = 0;
	double te = 10;
	double dt = 0.001;

	int nt = (te - ts)/dt;
	int nx = (xs - xe)/dx;

	double density[nx];
	// initialize the density
	for(int i=0; i<nx; i++) {
		density[i] = std::sin(xs + i*dx)
	}

	for(int i=0; i < nt; i++) {
		for(int j=1; j < nx - 1; j++) {
			density[j] = (density[j+1] + density[j-1] - 2*density[i])/dx/dx*dt 
			             + density[i]
		}
		density[0] = (density[2] + density[0] - 2*density[1])/dx/dx*dt 
			             + density[0]
		density[nx - 1] = (density[nx - 1] + density[nx - 3] - 2*density[nx - 2])/dx/dx*dt 
			             + density[nx - 1]
	}
	ofstream dfile;
	dfile.open("density.dat");
	for(int i=0; i<nx; i++) {
		dfile << xs + i*dx << "    " << density[i] << std::endl;
	}



	return 0;
}