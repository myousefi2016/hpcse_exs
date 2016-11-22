#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

x = []
y = []
f = open("output_den.dat")
lines = f.readlines()
for line in lines:
	data = line.split()
	x.append(float(data[0]))
	y.append(float(data[1]))

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Plot title...")    
ax1.set_xlabel('your x label..')
ax1.set_ylabel('your y label...')

ax1.plot(x,y, c='r', label='the data')

leg = ax1.legend()

plt.show()