CC=mpic++

CFLAGS=-std=c++11
INC=inc/

all:rank_size hello_world mp_int deadblock5 
	diffusion1d diffusion1d_class diffusion1d_mpi

rank_size:rank_size.cpp
	$(CC) $(CFLAGS) -o rank_size rank_size.cpp
hello_world:hello_world.cpp
	$(CC) $(CFLAGS) -o hello_world hello_world.cpp
mp_int:mp_int.cpp
	$(CC) $(CFLAGS) -o mp_int mp_int.cpp
deadblock5:deadblock5.cpp
	$(CC) $(CFLAGS) -o deadblock5 deadblock5.cpp
diffusion1d:diffusion1d.cpp
	g++ $(CFLAGS) -o diffusion1d diffusion1d.cpp
diffusion1d_class:diffusion1d_class.cpp
	g++ $(CFLAGS) -I $(INC) -o diffusion1d_class diffusion1d_class.cpp
diffusion1d_mpi:diffusion1d_mpi.cpp
	$(CC) $(CFLAGS) -I $(INC) -o diffusion1d_mpi diffusion1d_mpi.cpp
clean:
	rm -f rank_size hello_world mp_int deadblock5 diffusion1d diffusion1d_class
	diffusion1d_mpi
