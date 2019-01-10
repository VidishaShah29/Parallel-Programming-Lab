//read N elements of array where N is the size
//root sends one value to each process
//even ranked processes finds the square of the element
//odd ranked finds the cube
//buffered send

#include<mpi.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, i, x, n=100;
	int buff[n];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	MPI_Buffer_attach(buff,n);

	if(rank == 0){

		printf("\nEnter %d elements of the array: ",size-1);
		for(i=1; i<size; i++){
			scanf("%d",&x);
			MPI_Bsend(&x,1,MPI_INT,i,i,MPI_COMM_WORLD);
		}

	}
	else if(rank%2 == 0){

		MPI_Recv(&x,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		printf("\nReceived %d in rank %d, Square of the element: %d\n",x,rank,x*x);
	}

	else{

		MPI_Recv(&x,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		printf("\nReceived %d in rank %d, Cube of the element: %d\n",x,rank,x*x*x);
	}

	MPI_Buffer_detach(&buff,&n);
	MPI_Finalize();
	return 0;
}
