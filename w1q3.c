#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int a=9,b=3;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0){
		//Addition
		printf("Sum = %d\n",a+b);

	}
	if(rank == 1){
		//Subtraction
		printf("Difference = %d\n",a-b);

	}
	if(rank == 2){
			//Multiplication
			printf("Product = %d\n",a*b);

		}
	if(rank == 3){
			//Division
			if(b==0)
				printf("Division not possible\n");
			else printf("Quotient = %d\n",a/b);

		}
	MPI_Finalize();
	return 0;
}
