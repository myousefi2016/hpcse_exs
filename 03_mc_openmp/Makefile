CC=g++

CFLAGS=-Wall -O3 -std=c++11 -fopenmp

INC=inc/

all:ex01 ex02 ex03 simpson_serial simpson_openmp simpson_openmp_reduction pi pi_openmp pi_openmp_for openmp_for_ordered

ex01:ex01.cpp
	$(CC) $(CFLAGS) -o $@ $<
ex02:ex02.cpp
	$(CC) $(CFLAGS) -o $@ $<
ex03:ex03.cpp
	$(CC) $(CFLAGS) -o $@ $<
simpson_serial:simpson_serial.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)
simpson_openmp:simpson_openmp.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

simpson_openmp_reduction:simpson_openmp_reduction.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

pi:pi.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)
pi_openmp:pi_openmp.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)
pi_openmp_for:pi_openmp_for.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

openmp_for_ordered:openmp_for_ordered.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

clean:
	rm -rf ex01 ex02 ex03 simpson_serial simpson_openmp simpson_openmp_reduction pi pi_openmp pi_openmp_for openmp_for_ordered