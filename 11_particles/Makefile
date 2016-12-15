CC = mpic++
CFLAGS=-std=c++11 -Wall -O3
INC=inc/

.PHONY: all

all: nbody_serial_nocells 

nbody_serial_nocells: nbody_serial_nocells.cpp
	$(CC) $(CFLAGS) -o $@ $^ -I $(INC)

nbody_omp_cells: nbody_omp_cells.cpp
	#FILL IN COMPILE COMMAND HERE

.PHONY: clean

clean:
	rm -f nbody_serial_nocells nbody_omp_cells 
