
#include "VelocitySolverNSquared.h"

VelocitySolverNSquared::VelocitySolverNSquared(ArrayOfParticles & dstParticles, ArrayOfParticles & srcParticles, const int rank, const int size)
: dstParticles(dstParticles), srcParticles(srcParticles), rank(rank), size(size), timeC(0), timeT(0)
{
}

void VelocitySolverNSquared::ComputeVelocity()
{
    const double i2pi = 0.5/M_PI;
    const int N = dstParticles.Np;
    
    for (int pass=0; pass<size; pass++)
    {
        // 1. exchange
        Timer timerT;
        timerT.start();

        /* TODO 10.e: exchange particles */

        timerT.stop();
        timeT += timerT.get_timing();
        
        // 2. compute local
        Timer timerC;
        timerC.start();

        /* TODO 10.e: compute induced velocities by received particles at owned particle positions */

        timerC.stop();
        timeC += timerC.get_timing();
    }
}
