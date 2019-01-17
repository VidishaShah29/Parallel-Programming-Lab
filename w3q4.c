//read a string
//using n processes find the number of non vowels
//print the number found by each process in p0 and the total

#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[]){

	int rank, size,i, len, count=0, tot=0;
	char str[30], B[10];
	int C[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0){

		printf("\nEnter a string: ");
		gets(str);
		len = strlen(str);

	}

	MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str,len/size,MPI_CHAR,B,len/size,MPI_CHAR,0,MPI_COMM_WORLD);

	for(i=0; i<(len/size); i++){

		if(isalpha(B[i]))
			if(B[i]!='A' && B[i]!='a' && B[i]!='E' && B[i]!='e' && B[i]!='I' && B[i]!='i' && B[i]!='O' && B[i]!='o' && B[i]!='U' && B[i]!='u')
				count++;
	}

	MPI_Gather(&count,1,MPI_INT,C,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0){

			for(i = 0; i < size; i++){

				tot+=C[i];
				printf("\nP%d Count: %d",i,C[i]);
			}
			printf("\nTotal: %d",tot);
	}
	MPI_Finalize();
	printf("\n");

	return 0;
}
