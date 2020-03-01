#include <stdlib.h>
#include <stdio.h>

 
int main(int argc, char* argv[])
{
	int x,ones, pairs, tot;
	ones = 0;
	pairs = 0;
	tot = 0;
	x = atoi(argv[1]);
	while(x){
		if(x & 1){
			tot++;
			ones++;
		}else{
			ones = 0;
		}
		
		//Check to see if we have a pair
		if(ones == 2){
			pairs++;
			ones = 0;
		} 
	 x >>= 1;
	}

	if((tot % 2) == 0){
		printf("Even-Parity\t%d\n", pairs);
	}else{
		printf("Odd-Parity\t%d\n", pairs);
	}
}
