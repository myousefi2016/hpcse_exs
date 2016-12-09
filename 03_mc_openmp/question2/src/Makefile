CC=g++
CFLAGS=-std=c++11 -Wall -O3 -fopenmp
INC=inc/

all:monte_carlo_serial monte_carlo_openmp

monte_carlo_serial:monte_carlo_serial.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)
monte_carlo_openmp:monte_carlo_openmp.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

clean:
	rm -rf monte_carlo_serial monte_carlo_openmp
