#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, a;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0){

		a=5;
		printf("\nMaster with value = %d\n",a);

	}
	else{

		a=3;
		printf("\nWorker mode with value = %d\n",a);

	}
	MPI_Finalize();
	return 0;
}
