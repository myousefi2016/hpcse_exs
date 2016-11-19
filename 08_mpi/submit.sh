#bsub -n 4 -o rank_size.out mpirun ./rank_size
bsub -n 2 -o hello_world.out mpirun ./hello_world
