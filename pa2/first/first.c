#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short set(unsigned short x, int n, unsigned short v)
{
	if(v == 0){
		x = x & ~(1 << n);
	}else{
		x = x | (1 << n);
	}
	return x;
}
unsigned short comp(unsigned short x, int n)
{
	x = x ^ (1 << n);
	return x;
}
int get(unsigned short x, int n)
{
	unsigned short temp = (x >> n) & 1;
	return temp;
}

int main(int argc, char* argv[])
{
	FILE *fptr;
	if((fptr=fopen(argv[1], "r"))==NULL){
		printf("error");
		exit(0);
	}
	unsigned short x;
	char choice[100];
	fscanf(fptr, "%hu\n", &x);
	while(!feof(fptr)){
		int n;
		unsigned short v;
		fscanf(fptr, "%s\t%d\t%hu\n",choice, &n, &v);
		//printf("These are the commands and num: %s\t%d\t%hu\t%hu\n", choice, n, v, x);
		if(strcmp(choice, "get") == 0){
			//printf("In get");
			unsigned short result = get(x, n);
			printf("%hu\n", result);
		}
		else if(strcmp(choice, "comp") == 0){
			//printf("In comp");
			x = comp(x, n);
			printf("%d\n", x);
		}
		else if(strcmp(choice, "set") == 0){
			//printf("In set");
			x = set(x, n, v);
			printf("%d\n", x);
		}
	}
}
