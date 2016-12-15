#CC=g++
CC=mpic++

CFLAGS=-std=c++11 -Wall -O3

INC=inc/

all:io1_bin io1_bin_nocoll

io1_bin:io1_bin.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)
io1_bin_nocoll:io1_bin_nocoll.cpp
	$(CC) $(CFLAGS) -o $@ $< -I $(INC)

clean:
	rm -rf io1_bin io1_bin_nocoll