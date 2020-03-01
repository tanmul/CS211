#include <stdio.h>
#include <stdlib.h>

unsigned short get(unsigned short x, int n){
	unsigned short temp = (x >> n) & 1;
	return temp;
}
int main(int argc, char* argv[])
{
	//We have our number from the arg line
	unsigned short x = atoi(argv[1]);
	
	for(int i = 0; i < 8; i++){
		if(get(x, i) != get(x, 15-i)){
			printf("Not-Palindrome\n");
			return 0;
		}
	}
	printf("Is-Palindrome\n");
	return 0;
}
