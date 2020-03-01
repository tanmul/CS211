#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int row1, col1, row2, col2;
	FILE *fptr;
	if((fptr=fopen(argv[1],"r")) == NULL){
		printf("error");
		exit(0);
	}
	fscanf(fptr,"%d\t%d\n",&row1,&col1);
	int **matrix1 = (int**)malloc(row1*sizeof(int*));
	int i;
	for(i = 0; i < row1; i++){
		matrix1[i] = (int*)malloc(col1*sizeof(int));
	}

	int x, y;
	for(x = 0; x < row1; x++){
		for(y = 0; y < col1; y++){
			fscanf(fptr,"%d ",&i);
			matrix1[x][y] = i;
		}
	}
	fscanf(fptr,"%d\t%d\n",&row2,&col2);
	int **matrix2 = (int**)malloc(row2*sizeof(int*));
	for(i = 0; i < row2; i++){
		matrix2[i] = (int*)malloc(col2*sizeof(int));
	}
	i = 0;
	for(x = 0; x < row2; x++){
		for(y = 0; y < col2; y++){
			fscanf(fptr, "%d ",&i);
			matrix2[x][y] = i;
		}
	}
	if(col1 == row2){
		int** result = (int**)malloc(row1*sizeof(int*));
		for(i = 0; i < row1; i++){
			result[i] = (int*)malloc(col2*sizeof(int));
		}
		int j;
		for(i = 0; i < row1; i++){
			for(j = 0; j < col2; j++){
				result[i][j] = 0;
			}
		}
		int a, b;
		for(a = 0; a < row1; a++){
			for(b = 0; b < col2; b++){
				for(i = 0; i < col1; i++){
					result[a][b] += matrix1[a][i]*matrix2[i][b];
				}
			}
		}
		int r, c;
		for(r = 0; r < row1; r++){
			for(c = 0; c < col2; c++){
				printf("%d\t",result[r][c]);
			}
			printf("\n");
		}
	}else{
		printf("bad-matrices");
		return 0;
	}
	return 0;
}
