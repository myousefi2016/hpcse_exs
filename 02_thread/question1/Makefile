CC=g++
CFLAG=-std=c++11 -pthread
INC=inc/

all:diffusion2d diffusion2d_thread

diffusion2d:diffusion2d.cpp
	$(CC) $(CFLAG) -I $(INC) -o diffusion2d diffusion2d.cpp

diffusion2d_thread:diffusion2d_thread.cpp
	$(CC) $(CFLAG) -I $(INC) -o diffusion2d_thread diffusion2d_thread.cpp

clean:
	rm -rf diffusion2d diffusion2d_thread