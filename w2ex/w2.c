//standard send
#include<mpi.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){

		printf("\nEnter a number: ");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		printf("\n%d Sent from process 0",x);

	}
	else{

		MPI_Status status;
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("\nReceived %d in process 1\n",x);
	}

	MPI_Finalize();
	return 0;
}
