#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include "timer.hpp"


void write_rho(std::vector<double> rho, int N, double L, double dr, std::string filename)
{
	std::ofstream myfile;
	myfile.open(filename);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			myfile << i*dr - L/2 << "\t" << j*dr -L/2 <<"\t" << rho[i*N+j] << std::endl;
		}
	}
}

int main(int argc, char const *argv[])
{

	//input
	double L = 2;
	double D; // diffusion coefficient
	int N;  //
	double T;
	double dt;
	std::vector<double> rho;
	std::vector<double> rho_new;

	if(argc<5) {
		std::cout << "Please input D, N, t, dt" <<std::endl;
		return 1;
	}
	else {
		D = std::stod(argv[1]);
		N = std::stod(argv[2]);
		T = std::stod(argv[3]);
		dt = std::stod(argv[4]);
	}
	double dr = L/(N-1); // important!!! N-1 not N
	double coef = D*dt/dr/dr;
	rho.resize(N*N);
	rho_new.resize(N*N);
	//initial
	double boud = 1.0/2;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<N; ++j) {
			if(std::abs(i*dr-L/2)<boud && std::abs(j*dr-L/2)<boud) {
				rho[i*N + j] = 1;
			}
			else {
				rho[i*N + j] = 0;
			}
		}
	}
	write_rho(rho, N, L, dr, "input.dat");

	// rho_new = rho;

	//forward Euler and central difference
	double t = 0;
	int k = 0;
	std::string filename;
	while(t<T) {
		for(int i=0; i<N-1;++i) {
			for(int j=0;j<N-1;++j) {
				rho_new[i*N + j] = rho[i*N + j] + coef*(
					(i==N-1?0:rho[(i+1)*N + j]) + 
					(i==0?0:rho[(i-1)*N + j]) + 
					(j==N-1?0:rho[(i)*N + j+1]) + 
				 	(j==0?0:rho[(i)*N + j-1]) - 
				    4*rho[(i)*N + j]);
			}
		}

		t += dt;
		std::swap(rho, rho_new);
		// for(int i=1; i<N-1;i++) {
		// 	for(int j=0;j<N;j++) {
		// 		rho[i*N+j] = rho_new[i*N+j];			}
		// }
		if(k%100==0) {
			filename = "output_" + std::to_string(k) + ".dat";
			write_rho(rho, N, L, dr, filename);
		}
		k++;
	}
	//output
	// write_rho(rho, N, L, dr, "output.dat");
	return 0;
}