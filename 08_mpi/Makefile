CC=mpic++

CFLAGS=-std=c++11

all:rank_size hello_world mp_int deadblock5

rank_size:rank_size.cpp
	$(CC) $(CFLAGS) -o rank_size rank_size.cpp
hello_world:hello_world.cpp
	$(CC) $(CFLAGS) -o hello_world hello_world.cpp
mp_int:mp_int.cpp
	$(CC) $(CFLAGS) -o mp_int mp_int.cpp
deadblock5:deadblock5.cpp
	$(CC) $(CFLAGS) -o deadblock5 deadblock5.cpp

clean:
	rm -f rank_size hello_world mp_int deadblock5
