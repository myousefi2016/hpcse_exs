#ulimit -s unlimited
CC=g++
CFLAGS=-std=c++11 -msse4
INC=inc/

all:saxpy saxpy_simd sdot sdot_simd sdot_auto

sscal:sscal.cpp
	$(CC) $(CFLAGS) -o sscal sscal.cpp

saxpy:saxpy.cpp
	$(CC) $(CFLAGS) -I $(INC) -o saxpy saxpy.cpp
saxpy_simd:saxpy_simd.cpp
	$(CC) $(CFLAGS) -I $(INC) -o saxpy_simd saxpy_simd.cpp
sdot:sdot.cpp
	$(CC) $(CFLAGS) -I $(INC) -o sdot sdot.cpp
sdot_simd:sdot_simd.cpp
	$(CC) $(CFLAGS) -I $(INC) -o sdot_simd sdot_simd.cpp
sdot_auto:sdot_auto.cpp
	$(CC) $(CFLAGS) -ftree-vectorize -I $(INC) -o sdot_auto sdot_auto.cpp
clean:
	rm -rf sscal saxpy saxpy_simd sdot sdot_simd