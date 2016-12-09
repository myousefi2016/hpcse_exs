#!/usr/bin/env python
import numpy as np
import os

cores = [1, 2, 4, 8, 12, 16, 24]
D=1
L=2
Np = 10000
Nthreads = 4
T=0.01
Ns = 1024 
dt = 0.00001
for Nthreads in cores:
    os.system('src/diffusion2d_thread {0} {1} {2} {3} {4} {5} {6}' \
        .format(D, L, Ns, T, dt, Np, Nthreads) )

