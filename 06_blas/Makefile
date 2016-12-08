CC=g++

CFLAG=-std=c++11
LIBS=-lopenblas -lgfortran

all:ddot

ddot:ddot.cpp
	$(CC) $(CFLAG) -o ddot ddot.cpp $(LIBS) 

clean:
	rm -rf ddot