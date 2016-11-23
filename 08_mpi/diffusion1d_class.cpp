#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include "timer.hpp"


class Diffusion1D {
private:
	double D_, L_, dt_, dr_, fra_;
	int Nr_, Nt_;
	std::vector<double> rho_;
	std::vector<double> rho_tmp;

public:
	Diffusion1D(const double D, 
		        const double L, 
		        const int Nr, 
		        const int Nt, 
		        const double dt)
	:D_(D), L_(L), Nr_(Nr), Nt_(Nt), dt_(dt)  //Using Initialization Lists to Initialize 
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
};

int main(int argc, char const *argv[])
{
	int time = 0;
	timer t;
	if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " D L Nr Nt dt" << std::endl;
        return 1;
    }
	// Attention!!!
	// convergence condition (dt)/(dr)**2 < 1/2
	const double D  = std::stod(argv[1]);
    const double L  = std::stod(argv[2]);
    const int  Nr  = std::stoul(argv[3]);
    const int  Nt  = std::stoul(argv[4]);
    const double dt = std::stod(argv[5]);

    Diffusion1D MyDiff(D, L, Nr, Nt, dt);
		
    MyDiff.Initialization();
    MyDiff.Write("input");

    t.start();
    while(time < Nt) {
    	MyDiff.Solver();
    	time++;
    }
    t.stop();

    std::cout << "Timing : " << Nr << " " << 1 << " " << t.get_timing() << std::endl;
    
    MyDiff.Write("output");
	return 0;
}
