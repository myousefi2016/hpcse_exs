#include <iostream>
#include <timer.hpp>
#include <random>
#include <iomanip>
#include <cmath>
#include <omp.h>


class Randomwalk2D
{
public:
	int N_;
	double p_[2];
	double p_tmp[2];
	double d_, g;
	double pi=3.1415926;
	double rand;
	double mean;
	double sum, sum2, err;


	Randomwalk2D(double p[2], double d, int N)
	{
		//
		p_[0] = p[0];
		p_[1] = p[1];
		d_ = d;
		N_ = N;
		sum=0;
		sum2=0;
	}

	double Solver()
	{
		//
		p_tmp[0] = p_[0];
		p_tmp[1] = p_[1];
		while(1)
		{
		    // Choose a random mean between 1 and 6
			std::random_device rd;
		    std::mt19937 gen(rd());
		    std::uniform_real_distribution<double> dist(0, 1);
		    rand = dist(gen);
			p_tmp[0] += d_*std::cos(2*pi*rand);
			p_tmp[1] += d_*std::sin(2*pi*rand);
			if(p_tmp[0]<0 || p_tmp[0]>1 || p_tmp[1]<0 || p_tmp[1] >1) {
				g = p_tmp[0];
				return g;
			}
		}
	}

	double calcmean()
	{
		double sum_=0;
		double sum2_=2;
		#pragma omp parallel for reduction(+:sum_) reduction(+:sum2_)
		for(int i=0; i<N_; ++i) {
			g = Solver();
			sum_ += g;
			sum2_ += g*g;
		}
		sum = sum_;
		sum2 = sum2_;
		mean = sum/N_;
		return mean;
	}
	//
	double calcerror()
	{
		err = sqrt((sum2/N_ - mean*mean)/(N_-1));
		return err;
	}
	//
};

int main(int argc, char const *argv[])
{
	double p[2];
	int N=1000;
	double d=0.01;
	p[0] = 0.3;
	p[1] = 0.4;
	double mean, err;

	if(argc<4) {
		std::cout<<"Please input x, y, d, N" << std::endl;
		return 1;
	}
	p[0] = std::stod(argv[1]);
	p[1] = std::stod(argv[2]);
	d = std::stod(argv[3]);
	N = std::stod(argv[4]);

	Randomwalk2D MyWalk(p, d, N);
	timer time;
	time.start();
	mean = MyWalk.calcmean();
	err = MyWalk.calcerror();
	time.stop();

	// print the result
  	std::cout << "N: " << N << "\t" 
  			<< "time: " << time.get_timing() << "\t" 
            << "mean: " << std::setprecision(18) << mean << "\t"
            << "error: " << std::setprecision(18) << err << std::endl;
	
	return 0;
}