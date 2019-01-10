//read an int value in root process
//p0 to p1, p1 to p2 ... pn to p0
//each process increments the value while sending

#include<mpi.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0){

		printf("\nEnter a number for Master process: ");
		scanf("%d",&x);

		MPI_Ssend(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);

		MPI_Recv(&x,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
		printf("\nReceived %d from P%d to P%d\n",x,size-1,0);
	}
	else if(rank == size-1){

		MPI_Recv(&x,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);
		printf("\nReceived %d from P%d to P%d\n",x,rank-1,rank);
		x++;
		MPI_Ssend(&x,1,MPI_INT,0,rank,MPI_COMM_WORLD);
	}
	else{

		MPI_Recv(&x,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);
		printf("\nReceived %d from P%d to P%d\n",x,rank-1,rank);
		x++;
		MPI_Ssend(&x,1,MPI_INT,rank+1,rank,MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}
