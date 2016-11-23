#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <mpi.h>
#include "timer.hpp"


class Diffusion1D {
private:
	double D_, L_, dt_, dr_, fra_;
	int Nr_;
	std::vector<double> rho_tmp;

public:
	std::vector<double> rho_;

	Diffusion1D(const double D, 
		        const double L, 
		        const int Nr, 
		        const double dt)
	:D_(D), L_(L), Nr_(Nr), dt_(dt)  //Using Initialization Lists to Initialize 
	{
		//

		dr_ = L_/(Nr_-1);
		fra_ = D_*dt_/dr_/dr_;
		rho_.resize(Nr_);
		rho_tmp.resize(Nr_);
	}
	void Initialization() {
		for(int i =0; i< Nr_/2 - 1; i++) {
			rho_[i] = 1;
		}
		for(int i = Nr_/2 - 1; i< Nr_ - 1; i++) {
			rho_[i] = 0;
		}
		rho_tmp = rho_;
	}
	void Write(std::string filename) {
		std::ofstream out_file(filename);
		for(int i=0; i< Nr_; i++) {
			out_file << dr_*i << "    " << rho_[i] << std::endl;
		}
		out_file.close();
	}
	void Solver() {
		for(int i=1; i < Nr_ - 1; i++) {
			rho_tmp[i] = fra_*(rho_[i+1] + rho_[i-1] - 2*rho_[i]) 
			             + rho_[i];
		}
		std::swap(rho_, rho_tmp);
	}
	void set(double *rho) {
		for(int i=0; i<Nr_ - 1; i ++ ) {
			rho_[i] = rho[i];
		}
	}
};

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int size;
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0) {
		if (argc < 6) {
    		std::cerr << "Usage: " << argv[0] << " D L Nr Nt dt" << std::endl;
    		return 1;
		}
	}
	int time = 0;
	timer t;
	
	// Attention!!!
	// convergence condition (dt)/(dr)**2 < 1/2
	const double D  = std::stod(argv[1]);
    const double L  = std::stod(argv[2]);
    const int  Nr  = std::stoul(argv[3]);
    const int  Nt  = std::stoul(argv[4]);
    const double dt = std::stod(argv[5]);

    int lNr = (Nr - 1)/size + 1;
	// std::vector<double> rho_;
    Diffusion1D MyDiff(D, L, Nr, dt);
    Diffusion1D lDiff(D, L, lNr, dt);
		
    MyDiff.Initialization();
    MyDiff.Write("input");
    for(int i; i < lNr; i++) {
    	lDiff.rho_[i] = MyDiff.rho_[rank*(lNr - 1) + i];
    }
    while(time < Nt) {
    	if(rank==0) {
			MPI_Send(&lDiff.rho_[lNr-2], 1, MPI_DOUBLE, 1, 44, MPI_COMM_WORLD);
			MPI_Recv(&lDiff.rho_[lNr-1], 1, MPI_DOUBLE, 1, 44, MPI_COMM_WORLD, &status);
		}
		else if(rank==size-1) {
			MPI_Send(&lDiff.rho_[1], rank-1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD);
			MPI_Recv(&lDiff.rho_[0], rank-1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &status);

		}
		else {
			MPI_Send(&lDiff.rho_[1], rank-1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD);
			MPI_Recv(&lDiff.rho_[0], rank-1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &status);
			MPI_Send(&lDiff.rho_[lNr-2], rank+1, MPI_DOUBLE, rank+1, 44, MPI_COMM_WORLD);
			MPI_Recv(&lDiff.rho_[lNr-1], rank+1, MPI_DOUBLE, rank+1, 44, MPI_COMM_WORLD, &status);
		}
    	lDiff.Solver();
    	time++;
    }
    t.stop();
    if(rank==0) {
    	std::cout << "Timing : " << Nr << " " << 1 << " " << t.get_timing() << std::endl;
    }

    for(int i; i < lNr; i++) {
    	MyDiff.rho_[rank*(lNr - 1) + i] = lDiff.rho_[i];
    }
    MyDiff.Write("output");
    MPI_Finalize();	
	return 0;
}
