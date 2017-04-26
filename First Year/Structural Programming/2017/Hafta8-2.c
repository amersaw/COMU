#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3

int main(int argc, char *argv[]) {
	int a[MAX_SIZE][MAX_SIZE];
	int b[MAX_SIZE][MAX_SIZE];
	int c[MAX_SIZE][MAX_SIZE];
	int i,j;
	
	
	//a Matrisin elemanlari okuma
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("a[%d][%d] = ",i,j);
			scanf("%d",&a[i][j]);
		}
	}
	printf("\n###################################\n");
	//b Matrisin elemanlari okuma
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("b[%d][%d] = ",i,j);
			scanf("%d",&b[i][j]);
		}
	}
	
	//c=a+b Matrislerin toplama islemi
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	
	//c Matrisin elemanlari ekrana yazdirma
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
	
}