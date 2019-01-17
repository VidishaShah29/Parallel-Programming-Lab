//read m and nxm elements in root process
//send m elements to each process
//each process finds average and sends the value to root
//root finds the total average

#include<mpi.h>
#include<stdio.h>

int main(int argc, char* argv[]){

	int rank, size, m, n, A[30], B[30], i;
	float avg=0.0, tavg =0.0, C[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){

		n = size;
		printf("\nEnter a value- ");
		scanf("%d",&m);

		printf("\nEnter %d values- ",n*m);
		for(i = 0; i < n*m; i++)
				scanf("%d",&A[i]);
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,m,MPI_INT,B,m,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0; i<m; i++) avg += B[i];
	avg = avg/m;
	printf("\nRank: %d, Average: %f",rank,avg);

	MPI_Gather(&avg,1,MPI_FLOAT,C,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(rank == 0){

			for(i = 0; i < n; i++) {
						tavg += C[i];}
			printf("\nTotal average as in root- %f\n",tavg/n);
		}

	MPI_Finalize();
	printf("\n");

	return 0;
}
