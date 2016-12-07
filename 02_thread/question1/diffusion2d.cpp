#include <iostream>
#include <fstream>
#include "timer.hpp"

int main(int argc, char const *argv[])
{

	//input
	double D; // diffusion coefficient
	int N;  //
	double dt;
	if(argc<5) {
		std::cout << "Please input D, N, t, dt" <<std::endl;
		return 1;
	}
	else {
		D = argv[1];
		N = argv[2];
		T = argv[3];
		dt = argv[4];
	}
	double coef = D*dt/N/N;
	double rho[N*N]; //
	double dx = 1.0/N; //
	//initial
	for(int i=1; i<N/2; i++) {
		for(int j=0; j<N/2; j++) {
			rho[i*N + j] = 1;
		}
	}
	for(int i=N/2; i<N; i++) {
		for(int j=N/2; j<N; j++) {
			rho[i*N + j] = 0;
		}
	}
	double rho_new[N*N];
	rho_new = rho;

	//forward Euler and central difference
	double t = 0
	while(t<T) {
		for(int i=1; i<N-1;i++) {
			for(int j=0;j<N;j++) {
				rho_new[i*N + j] = rho[i*N + j] + coef*(
					rho[(i+1)*N + j] + rho[(i-1)*N + j] - 2rho[(i)*N + j]
				  + rho[(i)*N + j+1] + rho[(i)*N + j-1] - 2rho[(i)*N + j])
			}
		}
	}

	//output
	std::fstream myfile;
	myfile.open('output.dat');
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			myfile << i << "\t" << j <<"\t" << rho[i*N+j] << std::endl;
		}
	}
	return 0;
}