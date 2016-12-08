#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import os

cores = [1, 2, 4, 8, 12, 24]
D=1
L=2
Np = 10000
Nthreads = 4
T=0.1
Ns = 512
dt = 0.00001
for Nthreads in cores:
    os.system('./diffusion2d {0} {1} {2} {3} {4} {5} {6}' \
        .format(D, L, Ns, T, dt, Np, Nthreads) )

