#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt


files = [['density_000.dat', 'density_025.dat', 'density_050.dat', 'density_075.dat'],
         ['density_100.dat', 'density_125.dat', 'density_150.dat', 'density_175.dat']]

times = [[0.00, 0.25, 0.50, 0.75],
         [1.00, 1.25, 1.50, 1.75]]

N = 512 
Np = 1000

fig = plt.figure()

for i in range(8):
    fname = "output_{0}.dat".format(i*Np)
    data = np.loadtxt(fname)
    X = data[:,0].reshape((N,N))
    Y = data[:,1].reshape((N,N))
    VAL = data[:,2].reshape((N,N))
    
    ax = plt.subplot(2,4,i+1)
    im = plt.imshow(VAL, vmin=0, vmax=0.1, extent=(-1,1,-1,1))
    
   
    plt.xticks([-1,0,1])
    plt.yticks([-1,0,1])
    
    if i == 0:
        plt.xticks([])


fig.subplots_adjust(right=0.8)
cbar_ax = fig.add_axes([0.85, 0.15, 0.05, 0.7])
fig.colorbar(im, cax=cbar_ax)

plt.savefig('rho_serial.pdf')
plt.show()
