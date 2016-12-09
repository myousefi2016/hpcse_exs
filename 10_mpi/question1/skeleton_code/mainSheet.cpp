#include <fstream>
#include <sstream>
#include <iomanip>
#include "common.h"
#include "ArrayOfParticles.h"
#include "VelocitySolverNSquared.h"

using namespace std;

void WriteTimeToFile(const int Nranks, const double time, const char * sFileName)
{
    ofstream outfile;
    outfile.open(sFileName, ios::out | ios::app);
    outfile << Nranks << "    " << scientific << setprecision(6) <<  time << "\n";
    outfile.close();
}

void Dump(ArrayOfParticles& dstParticles, ArrayOfParticles& allParticles, const int Np, const int NpProcess, const int step, const int rank)
{

    /* TODO 10.f: write particle position, velocity and circulation to file: only rank 0 should write the data */
    
}

void DumpMPI(ArrayOfParticles& dstParticles, const int NpProcess, const int step, const int rank)
{

    /* TODO 10.f: write particle position, velocity and circulation to file: all ranks should write their data to a common file */

}

int main (int argc, char ** argv)
{
    int rank=0; // id of rank
    int size=1; // number of ranks
    /* TODO 10.b: initialization of MPI and setting of variables rank and size */
   
    // number of processes
    if (rank==0)
      std::cout << "Running with " << size << " MPI processes\n";
    
    // timer setup
    Timer timerIC, timerSim;
	
    // time integration setup
    const double dt = 0.001;
    const double tfinal = 2.5;
    const int ndump = 10;

    // output
    const bool bAnimation = true;
    const bool bVerbose = true;
    const bool dump_mpi = true;

    // number of particles
    const int N = 10000;
    size_t Np = (N/size)*size; // ensures that the number of particles is divisible by the number of workers
	
    timerIC.start();
    /* TODO 10.b: distribute particles such that each rank gets NpProcess particles */
    size_t NpProcess = 0;

    // particle vectors
    // dstParticles: particles owned by rank
    // srcParticles: particles with which the interaction has to be computed
    ArrayOfParticles dstParticles(NpProcess), srcParticles(NpProcess);
    ArrayOfParticles allParticles(rank==0 ? Np : 0); // list of all particles for output
    
    const double dx = 1./Np;
    double totGamma=0.; // total circulation is sum over gamma of all particles
    const double Gamma_s = 1.; 
    
    // initialize particles: position and circulation
    /* TODO 10.c: initialize particles (position and circulation) and compute total circulation totGamma */
    for (size_t i=0; i<NpProcess; i++)
    {

    }

    timerIC.stop();

    if (rank==0)
    {
      std::cout << "Number of particles: " << Np << std::endl;
      std::cout << "Number of particles per process: " << NpProcess << std::endl;
      std::cout << "Initial circulation: " << totGamma << std::endl;
      std::cout << "IC time: " << timerIC.get_timing() << std::endl;
    }
    
    // initialize velocity solver
    VelocitySolverNSquared VelocitySolver(dstParticles, srcParticles, rank, size);
	
    timerSim.start();
    double t=0;
    int it=0;
    for (it=1; it<=std::ceil(tfinal/dt); it++)
    {
      // reset particle velocities
      dstParticles.ClearVelocities(); 
      // compute velocities corresponding to time n
      VelocitySolver.ComputeVelocity();
        
      // dump the particles
      if ((it-1)%ndump==0 && bAnimation)
      {
        if (!dump_mpi)
          Dump(dstParticles,allParticles,Np,NpProcess,it-1,rank);
        else
          DumpMPI(dstParticles,NpProcess,it-1,rank);
      }
        
      // update time
      if (rank==0)
        t += dt;
      /* TODO 10.b: communicate time to all other ranks */
        
      if (it%ndump==0 && rank==0 && bVerbose)
        std::cout << "Iteration " << it << " time " << t << std::endl;
		
      // advance particles in time to n+1 using forward Euler
      dstParticles.AdvectEuler(dt);
      // update "source" particles
      srcParticles = dstParticles;
    }
    // dump final state
    if ((it-1)%ndump==0 && bAnimation)
    {
      if (!dump_mpi)
        Dump(dstParticles,allParticles,Np,NpProcess,it-1,rank);
      else
        DumpMPI(dstParticles,NpProcess,it-1,rank);
    }
    
    if (bVerbose)
      std::cout << "Bye from rank " << rank << std::endl;
    timerSim.stop();
    
    if (rank==0)
    {
      char buf[500];
      sprintf(buf, "timing.dat");
      WriteTimeToFile(size,timerSim.get_timing(),buf);
      std::cout << "#Ranks, Time - " << size << "\t" << timerSim.get_timing() << "\t( " << VelocitySolver.timeT << "\t" << VelocitySolver.timeC << " )\n";
    }

    /* TODO 10.b: finalize MPI */

    return 0;
}


