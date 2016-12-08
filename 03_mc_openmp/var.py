#!/usr/bin/env python

X = [100, 2.1, 3.1, 5, 6.5, 8]
X2 = []
N = len(X)
print(N)

EX = 0
EX2 = 0
for x in X:
	EX += x
	X2.append(x*x)
	EX2 += x*x

EX = EX/N
EX2 = EX2/N
DX = 0
for x in X:
	DX += (x - EX)*(x - EX)
DX = DX/N

print('Mean is {0}'.format(EX))
print('Var is {0}'.format(DX))
print('Var is {0}'.format(EX2 - EX**2))