#include <stdio.h>
#include <stdlib.h>

int isEven(int num){
	if(num%2==0){
		return 1;
	}
	return 0;
}

void sortOdd(int array[], int num, int count){
	if(num < array[count-1]){
		array[count]=num;
	}
	else{
		int i;
		for(i = 0; i < count; i++){
			if(num >= array[i]){
				int h = count;
				while(h > i){
					array[h] = array[h-1];
					h--;
				}
			array[i] = num;
			break;
			}
		}
	}
}
void sortEven(int array[], int num, int count){
	if(num > array[count-1]){
		array[count]=num;
	}
	else{
		int i;
		for(i = 0; i < count; i++){
			if(num <= array[i]){
				int h = count;
				while(h > i){
					array[h] = array[h-1];
					h--;
				}
			array[i] = num;
			break;
			}
		}
	}
}

int main(int arc, char *argv[]){
	int x;
	FILE *fptr;
	if((fptr = fopen(argv[1], "r")) == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}

	int numEle;
	fscanf(fptr, "%d\n", &numEle);

	int oddNum[numEle];
	int evenNum[numEle];
	int count = 0;
	int count2 = 0;

	while(!feof(fptr)){
		fscanf(fptr,"%d\n",&x);
		int even = isEven(x);

		//x is an odd number
		if(even == 0){
			if(count == 0){
				oddNum[0] = x;
			}else{
			sortOdd(oddNum,x,count);
			}
			count++;
		}
		//x is an even number
		else if(even == 1){
			if(count2 == 0){
				evenNum[0] = x;
			}else{
			sortEven(evenNum,x,count2);
			}
			count2++;
		}
	}

	//Enumerate the evennum array with the oddnum array
	int oddC;
	for(oddC=0; oddC<count;oddC++){
		evenNum[count2] = oddNum[oddC];
		count2++;
	}
	int final;
	for(final = 0; final < numEle; final++){
		printf("%d	", evenNum[final]);
	}
	return 0;
}
