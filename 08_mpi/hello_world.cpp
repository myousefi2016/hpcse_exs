#include <mpi.h>
#include <iostream>
int main(int argc, char const *argv[])
{
	MPI_Init(&argc, &argv);
	int num;
	MPI_Comm_rank(MPI_COMM_WORLD, &num);
	if(num==0){
		MPI_Status status;
		char txt[100];
		MPI_Recv(txt, 100, MPI_CHAR,
			1, 42, MPI_COMM_WORLD, &status)
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
