#include <stdio.h>
#include <stdlib.h>

#define N 10000
typedef struct Node{
	int data;
	struct Node* next;
} Node;

void chain(Node** head, int data){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	
	if(*head == NULL){
		*head = newNode;
	}else{
		Node *current = *head;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = newNode;
	}
}

int hash(int key){
	if(key < 0){
		key+=N;
	}
	return key%N;
}

int insert(Node** hashtable, int key){
	int hashKey = hash(key);
	//No Collisions
	if(hashtable[hashKey] == NULL){
		hashtable[hashKey] = malloc(sizeof(Node));
		Node *head = NULL;
		chain(&head, key);
		hashtable[hashKey] = head;
		return 0;
	}else{
	//Collision
	Node *head = hashtable[hashKey];
	chain(&head, key);
	hashtable[hashKey] = head;
	return 1;
	}
}

int search(Node** hashtable, int key){
	int hashKey = hash(key);

	if(hashtable[hashKey] == NULL){
		return 0;
	}else{
		Node *head = hashtable[hashKey];
		Node *current = head;
		while(current != NULL){
			if(current->data == key){
				return 1;
			}
			current = current->next;
		}
	}
	return 0;
}

int main(int argc, char* argv[]){
	FILE *fptr;
	if((fptr=fopen(argv[1],"r"))==NULL){
		printf("error");
		exit(0);
	}
	char command;
	int num;
	int totCol = 0;
	int totSearch = 0;
	Node** table = calloc(N, sizeof(Node));
	while(!feof(fptr)){
		fscanf(fptr, "%c\t%d\n",&command,&num);
		if(command == 'i'){
			totCol += insert(table,num);
		}else if(command == 's'){
			totSearch += search(table,num);
		}
	}
	
	printf("%d\n%d\n", totCol, totSearch);
	return 0;
}	
	
