#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int MPI_Errhadler(int errcode){

	if(errcode != MPI_SUCCESS){

		char errstring[200];
		int len, errclass;
		MPI_Error_class(errcode, &errclass);
		MPI_Error_string(errclass,errstring,&len);
		fprintf(stderr,"%s %d\n",errstring,len);
		MPI_Error_string(errcode,errstring,&len);
		fprintf(stderr,"HELLO_ERRCODE %s \n",errstring);
	}
}

int main(int argc , char *argv[]) {

	int rank, size, len, errcode, c=3;

	errcode = MPI_Init(&argc, &argv) ;
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	errcode = MPI_Comm_size(c, &size) ;
	MPI_Errhadler(errcode);
	printf("\nRank: %d Size: %d\n",rank,size);
	MPI_Finalize();

}
