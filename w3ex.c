#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){

	int rank, size, N, A[10], B[10], c, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){

		N = size;
		printf("\nEnter %d values- ",N);
		for(i = 0; i < N; i++) scanf("%d",&A[i]);
	}

	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("\nI have received %d in P%d",c,rank);
	c = c*c;

	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0){

			printf("\nResult gathered in root- ");
			for(i = 0; i < N; i++) printf("%d ",B[i]);
		}

	MPI_Finalize();
	printf("\n");
	return 0;
}
