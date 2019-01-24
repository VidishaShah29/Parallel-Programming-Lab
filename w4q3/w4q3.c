#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {

	int rank, size, ele, count=0, i, tot=0;
	int arr[9], temp[9];

	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;

	if(rank == 0){
		printf("\nEnter a 3x3 matrix: \n");
		for(i=0; i<9; i++)
			scanf("%d",&arr[i]);

		printf("\nEnter an element to be searched: ");
		scanf("%d",&ele);
	}

	MPI_Bcast(&ele, 1, MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr, 9/size, MPI_INT, temp, 9/size, MPI_INT, 0 , MPI_COMM_WORLD) ;

	for(i=0; i<9/size; i++)
		if(temp[i] == ele)
			count++;

	printf("\nCount of ele in rank %d is: %d\n",rank,count);

	MPI_Reduce(&count, &tot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
			printf("\nCount of ele in the given array is: %d\n",tot);
	}

	MPI_Finalize();
	return 0;
}
