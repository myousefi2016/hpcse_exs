#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include "timer.hpp"

class Diffusion2D {
private:
	void Initial() {
		double boud = L_/4;
		for(int i=0; i<N_; ++i) {
			for(int j=0; j<N_; ++j) {
				if(std::abs(i*dr_-L_/2)<boud && std::abs(j*dr_-L_/2)<boud) {
					rho_[i*N_ + j] = 1;
				}
				else {
					rho_[i*N_ + j] = 0;
				}
			}
		}
	}

public:
	double D_; // diffusion coefficient
	int N_, Nthreads_;  //
	double T_, dt_, L_, dr_;
	std::vector<double> rho_, rho_new;
	double coef_;

	//
	Diffusion2D(double D, double L, int N, double T, double dt, int Nthreads) {
		D_ = D;
		L_ = L;
		N_ = N;
		T_ = T;
		dt_ = dt;
		dr_ = L_/(N_-1);
		Nthreads_ = Nthreads;
		coef_ = D_*dt_/dr_/dr_;
		rho_.resize(N*N);
		rho_new.resize(N*N);
		Initial();
	}

	// Solve
	void Solve() {
		std::vector<std::thread> Threads_(Nthreads_);
		for(int k=0; k<Nthreads_; ++k) {
			
			Threads_[k] = std::thread( [k, this] () {   // why & not work?? this mean the class??
				int begin = k*N_/Nthreads_;
				int end = (k+1)*N_/Nthreads_;
				for(int i=begin; i<end;++i) {
					for(int j=0;j<N_;++j) {
						rho_new[i*N_ + j] = rho_[i*N_ + j] + coef_*(
							(i==N_-1?0:rho_[(i+1)*N_ + j]) + 
							(i==0?0:rho_[(i-1)*N_ + j]) + 
							(j==N_-1?0:rho_[(i)*N_ + j+1]) + 
						 	(j==0?0:rho_[(i)*N_ + j-1]) - 
						    4*rho_[(i)*N_ + j]);
					}
				}
			}
			);
		}
		for(auto & t:Threads_) {
			t.join();
		}
		
		std::swap(rho_, rho_new);
	}
	//
	void Write_rho(std::string filename) {
		std::ofstream myfile;
		myfile.open(filename);
		for(int i=0; i<N_; i++) {
			for(int j=0; j<N_; j++) {
				myfile << i*dr_ - L_/2 << "\t" << j*dr_ -L_/2 <<"\t" << rho_[i*N_+j] << std::endl;
			}
		}
		myfile.close();
	}
};


int main(int argc, char const *argv[])
{

	//input
	if(argc<8) {
		std::cout << "Please input D, L, N, t, dt, Np, Nthreads" <<std::endl;
		return 1;
	}
	
	double D = std::stod(argv[1]); // diffusion coefficient
	double L = std::stod(argv[2]);
	int N = std::stod(argv[3]);
	double T = std::stod(argv[4]);
	double dt = std::stod(argv[5]);
	int Np = std::stod(argv[6]);
	int Nthreads = std::stod(argv[7]);
	//initial
	Diffusion2D MyDiff(D, L, N, T, dt, Nthreads);

	//forward Euler and central difference
	timer time;
	double t = 0;
	int k = 0;
	std::string filename;
	time.start();
	while(t<T) {
		if(k%Np==0) {
			filename = "output_" + std::to_string(k) + ".dat";
			MyDiff.Write_rho(filename);
		}

		t += dt;
		MyDiff.Solve();
		
		k++;
	}
	time.stop();
	std::cout << "threads: " << Nthreads << "\t" 
			  // << D << "\t" 
	          // << L << "\t" 
	          // << N << "\t" 
	          // << t << "\t" 
	          // << dt << "\t" 
	          // << Np << "\t" 
	          << "time: " << time.get_timing() << std::endl;
	//output
	// Write_rho(rho, N, L, dr, "output.dat");
	return 0;
}