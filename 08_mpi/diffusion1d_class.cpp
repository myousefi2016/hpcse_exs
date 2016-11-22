#include <iostream>
#include <cmath>
#include <fstream>

class Diffusion1 {
public:
	Diffusion1(double L, int N, double dt, ) {
		//
		dr = L/(N-1);
	}
}

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

	double den[100000];
	double den_new[100000];
	// initialize the den
	std::cout << "xs = " << xs
	          << "\n xe = " << xe
	          << "\n nx = " << nx
	          << "\n ts = " << te
	          << "\n te = " << te
	          << "\n nt = " << nt << std::endl;
 
	for(int i=1; i< nx - 1; i++) {
		den[i] = 1;
	}
	den[0] = 0;
	den[1] = 0;
 
	std::ofstream input;
	input.open("input_den.dat");
	for(int i=0; i<nx; i++) {
		input << xs + i*dx << "    " << den[i] << std::endl;
	}

	for(int i=0; i < nt; i++) {
		for(int j=1; j < nx - 1; j++) {
			den_new[j] = (den[j+1] + den[j-1] - 2*den[j])/dx/dx*dt 
			             + den[j];
		}
		for(int j=1; j < nx - 1; j++) {
			den[j] = den_new[j];
		}
	}
	std::ofstream output;
	output.open("output_den.dat");
	for(int i=0; i<nx; i++) {
		output << xs + i*dx << "    " << den[i] << std::endl;
	}



	return 0;
}