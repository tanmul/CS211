#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
} Node;

Node* createNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

void inorderTraversal(Node *root){
	if(root != NULL){
		inorderTraversal(root->left);
		printf("%d\t",root->data);
		inorderTraversal(root->right);
	}
}

Node* insert(Node* root, int data){
	if(root == NULL){
		return createNode(data);
	}
	if(data < root->data){
		root->left = insert(root->left, data);
	}else if(data > root->data){
		root->right = insert(root->right, data);
	}
	return root;
}

int main(int argc, char *argv[]){
	Node* root = NULL;
	char command;
	int num;
	FILE *fptr;
	if((fptr = fopen(argv[1], "r")) == NULL){
		printf("error");
		exit(0);
	}
	fscanf(fptr, "%c\t%d\n",&command,&num);
	root = insert(root, num);
	while(!(feof(fptr))){
		fscanf(fptr, "%c\t%d\n",&command,&num);
		if(command == 'i'){
			insert(root, num);	
		}
	}
	inorderTraversal(root);
	return 0;
}

