#bsub -n 4 -o rank_size.out mpirun ./rank_size
bsub -n 4 -o hello_world.out mpirun ./hello_world
#bsub -n 2 -o mp_int.out mpirun ./mp_int
#bsub -n 2 -o deadblock5.out mpirun ./deadblock5
