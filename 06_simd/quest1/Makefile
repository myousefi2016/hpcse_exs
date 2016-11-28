#ulimit -s unlimited
CC=g++
CFLAGS=-std=c++11 -msse4
INC=inc/

all:binomial binomial_simd binomial_auto

binomial:binomial.cpp
	$(CC) $(CFLAGS) -I $(INC) -o binomial binomial.cpp
binomial_simd:binomial_simd.cpp
	$(CC) $(CFLAGS) -I $(INC) -o binomial_simd binomial_simd.cpp
binomial_auto:binomial_auto.cpp
	$(CC) $(CFLAGS) -ftree-vectorize -I $(INC) -o binomial_auto binomial_auto.cpp
clean:
	rm -rf  binomial binomial_simd binomial_auto