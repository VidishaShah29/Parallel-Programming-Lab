#include<stdio.h>
#include<stdlib.h>

int main(){

	printf("\nEnter dimensions of Mat1: ");
	int a,b,i,j;
	scanf("%d %d",&a,&b);

	printf("\nEnter dimensions of Mat2: ");
	int p,q;
	scanf("%d %d",&p,&q);

	if(b!=p){
		printf("\nMultiplication of Matrices not possible!");
		exit(0);
	}

	int mat1[a][b],mat2[p][q];

	printf("\nEnter Mat1: ");
	for(i=0; i<a; i++)
		for(j=0; j<b; j++)
			scanf("%d",&mat1[i][j]);

	printf("\nEnter Mat2: ");
	for(i=0; i<p; i++)
		for(j=0; j<q; j++)
			scanf("%d",&mat2[i][j]);

	int mat[a][q],k;
	for(i=0; i<a; i++)
		for(j=0; j<q; j++){
			mat[i][j] = 0;
			for(k=0; k<b; k++)
				mat[i][j] += mat1[i][k]*mat2[k][j];
		}
	printf("\nOutput: \n");
	for(i=0; i<a; i++){
		for(j=0; j<q; j++){
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}

}
