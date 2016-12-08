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

public:

	std::vector<double> rho_;
	std::vector<double> rho_tmp;

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
	void Solver(int rank, int size, MPI_Status status, MPI_Request reqs[4]) {
		if(rank==0) {
			MPI_Isend(&rho_[Nr_-2], 1, MPI_DOUBLE, 1, 44, MPI_COMM_WORLD, &reqs[0]);
			MPI_Irecv(&rho_[Nr_-1], 1, MPI_DOUBLE, 1, 44, MPI_COMM_WORLD, &reqs[1]);
		}
		else if(rank==size-1) {
			MPI_Isend(&rho_[1], 1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &reqs[0]);
			MPI_Irecv(&rho_[0], 1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &reqs[1]);
		}
		else {
			MPI_Isend(&rho_[1], 1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &reqs[0]);
			MPI_Irecv(&rho_[0], 1, MPI_DOUBLE, rank-1, 44, MPI_COMM_WORLD, &reqs[1]);
			MPI_Isend(&rho_[Nr_-2], 1, MPI_DOUBLE, rank+1, 44, MPI_COMM_WORLD, &reqs[2]);
			MPI_Irecv(&rho_[Nr_-1], 1, MPI_DOUBLE, rank+1, 44, MPI_COMM_WORLD, &reqs[3]);
		}
		//
		for(int i=2; i < Nr_ - 2; i++) {
			rho_tmp[i] = fra_*(rho_[i+1] + rho_[i-1] - 2*rho_[i]) 
			             + rho_[i];
		}
		if(rank==0 || rank==size-1) {
        	MPI_Waitall(2, reqs, &status);
		}
		else
		{
        	MPI_Waitall(4, reqs, &status);
		}
		std::swap(rho_, rho_tmp);
		//
		
	}
	void Set(double *rho) {
		for(int i=0; i<Nr_ - 1; i ++ ) {
			rho_[i] = rho[i];
		}
	}
};

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request reqs[4];
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
    for(int i = 0; i < lNr; i++) {
    	lDiff.rho_[i] = MyDiff.rho_[rank*(lNr - 1) + i];
    	lDiff.rho_tmp[i] = MyDiff.rho_[rank*(lNr - 1) + i];
    }
    double ds = 0;
    double dr = 0;

    t.start();

    // std::cout << rank << "\t" << size << std::endl;
    while(time < Nt) {
    	lDiff.Solver(rank, size, status, reqs);
    	time++;
    }
    t.stop();
    if(rank==0) {
    	std::cout << "Timing : " << Nr << " " << 1 << " " << t.get_timing() << std::endl;
    }

    for(int i=0; i < lNr; i++) {
    	MyDiff.rho_[rank*(lNr - 1) + i] = lDiff.rho_[i];
    	// std::cout << rank*(lNr - 1) + i << "\t" << MyDiff.rho_[rank*(lNr - 1) + i] << std::endl;
    }
    if(rank==0) {
    	// MPI_Barrier(MPI_COMM_WORLD);
    	MyDiff.Write("output");
    }
    MPI_Finalize();	
	return 0;
}
