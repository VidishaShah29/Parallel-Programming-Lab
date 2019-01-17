#include<mpi.h>
#include<stdio.h>

int fact(int c){

	int f=1;
	if(c == 0)
		return 1;
	for(int i=c; i>0; i--) f = f*i;
	return f;
}

int main(int argc, char* argv[]){

	int rank, size, N, A[10], c, i, sum=0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){

		N = size;
		printf("\nEnter %d values- ",N);
		for(i = 0; i < N; i++) scanf("%d",&A[i]);
	}

	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	int f = fact(c);
	printf("\nI have received %d in P%d, Factorial is %d",c,rank,f);

	MPI_Reduce(&f,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank == 0)
	printf("\nSum of the factorials is %d",sum);

	MPI_Finalize();
	printf("\n");

	return 0;
}
