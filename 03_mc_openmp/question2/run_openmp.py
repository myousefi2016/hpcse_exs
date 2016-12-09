#!/usr/bin/env python
import numpy as np
import os

x=0.3
y=0.4
N = 10000
d = 0.01
for i in range(15):
    os.system('src/monte_carlo_openmp {0} {1} {2} {3} ' \
        .format(x, y, d, 2**i) )

