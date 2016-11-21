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
	int nx = (xe - xs)/dx;

	double density[1000000];
	// initialize the density
	std::cout << "xs = " << xs
	          << "\n xe = " << xe
	          << "\n nx = " << nx
	          << "\n ts = " << te
	          << "\n te = " << te
	          << "\n nt = " << nt << std::endl;
 
	for(int i=0; i<nx; i++) {
		density[i] = std::sin(xs + i*dx);
	}

	std::ofstream input;
	input.open("input_density.dat");
	for(int i=0; i<nx; i++) {
		input << xs + i*dx << "    " << density[i] << std::endl;
	}

	for(int i=0; i < nt; i++) {
		for(int j=1; j < nx - 1; j++) {
			density[j] = (density[j+1] + density[j-1] - 2*density[j])/dx/dx*dt 
			             + density[j];
		}
		density[0] = (density[2] + density[0] - 2*density[1])/dx/dx*dt 
			             + density[0];
		density[nx - 1] = (density[nx - 1] + density[nx - 3] - 2*density[nx - 2])/dx/dx*dt 
			             + density[nx - 1];
	}
	std::ofstream output;
	output.open("output_density.dat");
	for(int i=0; i<nx; i++) {
		output << xs + i*dx << "    " << density[i] << std::endl;
	}



	return 0;
}
