
#ifndef ARRAYOFPARTICLE_H
#define ARRAYOFPARTICLE_H

#include "common.h"

class ArrayOfParticles
{
public:
    int Np;
    double * x;
    double * y;
    double * u;
    double * v;
    double * gamma;
    
    ArrayOfParticles(int Np) : Np(Np)
    {
        x     = new double[Np];
        y     = new double[Np];
        u     = new double[Np];
        v     = new double[Np];
        gamma = new double[Np];
        
        for (int i=0; i<Np; i++)
        {
          x[i]     = 0.;
          y[i]     = 0.;
          u[i]     = 0.;
          v[i]     = 0.;
          gamma[i] = 0.;
        }
    }
    
    ~ArrayOfParticles()
    {
        delete [] x;
        delete [] y;
        delete [] u;
        delete [] v;
        delete [] gamma;
    }
    
    ArrayOfParticles& operator=(ArrayOfParticles &p)
    {
        Np = p.Np;
        
        for (int i=0; i<Np; i++)
        {
          x[i]     = p.x[i];
          y[i]     = p.y[i];
          u[i]     = p.u[i];
          v[i]     = p.v[i];
          gamma[i] = p.gamma[i];
        }
        return *this;
    }
    
    void AdvectEuler(double dt)
    {
        /* TODO 10.d: update of particle positions based on forward Euler scheme */
    }
    
    void ClearVelocities()
    {
        for (int i=0; i<Np; i++)
        {
          u[i] = 0.;
          v[i] = 0.;
        }
    }
};

#endif /* ARRAYOFPARTICLE_H */
