#!/usr/bin/evn python
import numpy as np
import itertools

def T1(v):
	tmp = v[:]
	tmp[0] = v[1]
	tmp[1] = v[0]
	return tmp
def T2(v):
	tmp = v
	tmp[0][0] = v[0][2]
	tmp[0][2] = v[0][0]
	tmp[1][0] = v[1][2]
	tmp[1][2] = v[1][0]
	return tmp
def T3(v):
	tmp = v
	tmp[0] = v[1]
	tmp[1] = v[0]
	tmp1 = tmp
	tmp[0][0] = tmp1[0][2]
	tmp[0][2] = tmp1[0][0]
	tmp[1][0] = tmp1[1][2]
	tmp[1][2] = tmp1[1][0]
	return tmp
#===========================================
a0 = [[[ 0, 1, 0], [ 1, 0, 1]]]
print(T1(a0[0]))
print(a0)