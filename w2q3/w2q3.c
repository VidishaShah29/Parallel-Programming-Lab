//add an array of size N using 2 processes
//result in root process
//analyze time taken in each process

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int rank, size, n, i, sum1=0, sum2=0;
	int arr[20];
	double t1,t2;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0){

		printf("\nEnter the size of the array: ");
		scanf("%d",&n);

		printf("\nEnter the elements of the array: ");
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);

		MPI_Ssend(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend(arr,n,MPI_INT,1,1,MPI_COMM_WORLD);

		t1 = MPI_Wtime();
		for(i=0; i<n/2; i++) sum1+=arr[i];
		t2 = MPI_Wtime();

		printf("\nTime taken by Process 0: %f",t2-t1);

		MPI_Recv(&sum2,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
		printf("\n\nSum of the elements of the Array: %d\n",sum2+sum1);

	}
	else{

		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(arr,n,MPI_INT,0,1,MPI_COMM_WORLD,&status);

		t1 = MPI_Wtime();
		for(i=n/2; i<n; i++) sum2+=arr[i];
		t2 = MPI_Wtime();

		printf("\nTime taken by Process 1: %f",t2-t1);

		MPI_Ssend(&sum2,1,MPI_INT,0,2,MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}
