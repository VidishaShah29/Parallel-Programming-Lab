#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc , char *argv[]) {

	int rank, size, i, n;
	double PI25DT = 3.141592653589793238462643;
	double mypi, pi, h, sum=0.0, x;

	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;

		if(rank == 0){
			printf("\nEnter the number of intervals, 0 quits: ");
			scanf("%d",&n);
		}

	MPI_Bcast(&n, 1, MPI_INT,0,MPI_COMM_WORLD);

	if(n == 0) exit(0);

	h = 1.0/(double)(n);

	for(i=rank+1; i<=n; i+=size){

		x = h * ((double)i - 0.5);
		sum += 4.0/(1.0 + x*x);
	}

	mypi = h * sum;

	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){

		printf("\n pi is approximately %.16f, Error is %.16f\n", pi,(pi - PI25DT));
	}

	MPI_Finalize();
	return 0;
}
