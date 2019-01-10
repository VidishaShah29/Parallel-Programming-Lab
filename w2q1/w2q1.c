//synchronous send
#include<mpi.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int rank, size, len;
	char word[256];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0){

		printf("\nEnter a word to be sent from process 0: ");
		gets(word);
		len = strlen(word);

		MPI_Ssend(&len,1,MPI_INT,1,0,MPI_COMM_WORLD);

		MPI_Ssend(word,len,MPI_CHAR,1,1,MPI_COMM_WORLD);

		MPI_Recv(word,len,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);

		printf("\nToggle word received from process 1: ");
		puts(word);

	}
	else{

		MPI_Recv(&len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(word,len,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		printf("\nReceived word in process 1: ");
		puts(word);

		for(int i=0; i<len; i++){

			if(word[i]>=65 && word[i]<=90) word[i]+=32;
			else if(word[i]>=97 && word[i]<=122) word[i]-=32;

		}

		MPI_Ssend(word,len,MPI_CHAR,0,2,MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}
