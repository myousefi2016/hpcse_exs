#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import os

D=1
L=2
Np = 10000
Nthreads = 4
T=[1, 0.1, 0.001]
Ns = [128, 256, 1024]
dt = [0.00001, 0.000001, 0.00000001]
for i in range(3):
    os.system('./diffusion2d {0} {1} {2} {3} {4} {5} {6}' \
        .format(D, L, Ns[i], T[i], dt[i], Np, Nthreads) )

