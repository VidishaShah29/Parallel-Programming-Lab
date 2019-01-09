#include "mpi.h"
#include<stdio.h>

int checkprime(int num)
{
	for(int i=2; i<num/2; i++)
		if(num%i == 0)
			return 0;

	return 1;
}

int main(int argc, char *argv[])
{
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0){

		for(int i=2; i<51; i++)

			if(i%2 != 0 || i==2)
				if(checkprime(i)==1)
					printf("\n%d - rank %d",i,rank);
	}
	if(rank == 1){

		for(int i=51; i<101; i++)
					if(i%2 != 0)
						if(checkprime(i)==1)
							printf("\n%d - rank %d",i,rank);
	}
	MPI_Finalize();
		return 0;
	}
