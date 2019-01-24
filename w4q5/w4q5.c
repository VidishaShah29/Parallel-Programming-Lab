#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {

	int rank, size, i;
	int arr[16], temp[16], final[16];

	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;

	if(rank == 0){
		printf("\nEnter a 4x4 matrix: \n");
		for(i=0; i<16; i++)
			scanf("%d",&arr[i]);
		printf("\nOutput matrix: \n");

	}

	MPI_Scatter(arr, 16/size, MPI_INT, temp, 16/size, MPI_INT, 0 , MPI_COMM_WORLD) ;

	MPI_Scan(&temp, &final, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);



	for(i=0; i<4; i++)
		printf("%d ",final[i]);
	printf("\n");


	MPI_Finalize();
	return 0;
}
