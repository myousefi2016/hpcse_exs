# TODO 10.b: DEFINE TOOLS
CC = 

.PHONY: all
all: sheet

sheet: mainSheet.o VelocitySolverNSquared.o 
	# TODO 10.b: FILL IN COMPILE COMMAND HERE

%.o: %.cpp
	$(CC) -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -f sheet
