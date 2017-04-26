#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3

int main(int argc, char *argv[]) {
	int a[MAX_SIZE][MAX_SIZE];
	int i,j;
		
	//Matris elemanlari okuma
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("a[%d][%d] = ",i,j);
			scanf("%d",&a[i][j]);
		}
	}
	
	//Matris elemanlari ekrana yazdirma
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
	
}