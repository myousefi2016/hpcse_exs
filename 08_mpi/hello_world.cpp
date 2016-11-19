#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int num;
	MPI_Comm_rank(MPI_COMM_WORLD, &num);
	if(num==0){
		MPI_Status status;
		int count;
		char txt[100];
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		std::cout << "A message is waiting from " << status.MPI_SOURCE
		          << " with tag "                  << status.MPI_TAG;
		MPI_Recv(txt, 100, MPI_CHAR,
			1, 42, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		std::cout << " and assuming it contains ints there are " << count 
                          << " elements" << "\n";
		std::cout << txt << "\n";
	}
	else{
		std::string txt = "Hello world!";
		MPI_Send(const_cast<char*>(txt.c_str()), txt.size()+1, MPI_CHAR,
			0, 42, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
