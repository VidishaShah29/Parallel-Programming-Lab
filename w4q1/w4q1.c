#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {

	int rank, size, fact = 1, factsum = 0, i;

	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;

	for(i=1; i<=rank+1; i++)
		fact*=i;

	printf("\nFactorial of %d = %d\n", rank+1, fact);

	MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	if(rank == size-1)
		printf("\nSum of all the factorial is %d\n",factsum);

	MPI_Finalize();
	return 0;
}
