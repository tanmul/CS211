#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  //Create an array of vowels to use for comparisons
  char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
  int i = 0;
  for(i=1; i<argc;i++){
    char* letter = argv[i];
    int j = 0;
    while(*letter != '\0'){
      for(j =0; j < 5; j++){
        if(*letter == vowels[j]){
          printf("%c", *letter);
          break;
        }
      }
      letter++;
    }
  }
  printf("\n");
  return 0;
}
