CC=mpicxx

CFLAGS=-std=c++

all:rank_size hello_world

rank_size:rank_size.cpp
	$(CC) --std=c++11 -o rank_size rank_size.cpp
rank_size:hello_world.cpp
	$(CC) --std=c++11 -o hello_world hello_world.cpp
rank_size:mp_int.cpp
	$(CC) --std=c++11 -o mp_int mp_int.cpp

clean:
	rm -f rank_size, hello_world mp_int
