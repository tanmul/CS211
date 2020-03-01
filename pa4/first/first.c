#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
	char name[100];
	int bit;
	struct node* next;
}node;

typedef struct gateNode{
	char name[100];
	char operand1[21];
	char operand2[21];
	char output[21];
	struct gateNode* next;
}gateNode;



node* add(node* root, char* name){
	if(root==NULL){
	    root=malloc(sizeof(node));
	    strcpy(root->name,name);
	    root->next=NULL;
	    return root;
	}
	node* ptr=root;
	while(ptr->next!=NULL){
	    ptr=ptr->next;
	}
	node* new =malloc(sizeof(node));
	strcpy(new->name,name);
	new->next=NULL;
	ptr->next=new;
	return root;
}

gateNode* addg(gateNode* root, char* name, char* operand1, char* operand2, char* output){
	if(root == NULL){
		root = malloc(sizeof(gateNode));
		strcpy(root->name, name);
		strcpy(root->operand1, operand1);
		strcpy(root->operand2, operand2);
		strcpy(root->output, output);
		root->next = NULL;
		return root;
	}
	gateNode* ptr = root;
	while(ptr->next!= NULL){
		ptr = ptr->next;
	}
	gateNode* new = malloc(sizeof(gateNode));
	strcpy(new->name, name);
	strcpy(new->operand1, operand1);
	strcpy(new->operand2, operand2);
	strcpy(new->output, output);
	new->next = NULL;
	ptr->next = new;
	return root;
}


//Find Methods

int findint(char* name, node* root){
	node* ptr = root;
	while(ptr!=NULL){
		if(strcmp(name, ptr->name) == 0){
			return ptr->bit;
		}
	ptr=ptr->next;
	}
	return 2;
}


int findout(char* name,int n, node* root){
	node* ptr =root;
	while(ptr!=NULL){
		if(strcmp(name, ptr->name) == 0){
			ptr->bit=n;
			return 1;
		}
	ptr=ptr->next;
	}
	return 2;
}

//Matrix and Lists
void printMatrix(int** matrix, int row, int column){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void printList(node* root){
	node* ptr = root;
	while(ptr != NULL){
		printf("%s\t%d\n", ptr->name, ptr->bit);
		ptr = ptr->next;
	}
}

int bit(int total,int n,int num){
	int s=total-n-1;
	int b;
	b=(num>>s)&1;
	if(b==1){
	  return 1;
	}
	if(b==0){
	  return 0;
	}

	printf("error\n");
	return 2;
}

//Gates
int not(int input){
  if(input==1){
    return 0;
  }
  return 1;
}

int and(int operand1,int operand2){
  if(operand1==1&&operand2==1){
    return 1;
  }
  return 0;
}

int or(int operand1,int operand2){
  if(operand1==1||operand2==1){
    return 1;
  }

  return 0;
}

int nand(int operand1,int operand2){
  if(operand1==1&&operand2==1){
    return 0;
  }

  return 1;
}

int nor(int operand1,int operand2){
  if(operand1==1||operand2==1){
    return 0;
  }

  return 1;
}

int xor(int operand1,int operand2){
  if(operand1==1&&operand2==0){
    	return 1;
  }else if(operand1==0&&operand2==1){
	return 1;
  }
  return 0;
}


int main(int argc, char* argv[]){
	FILE *fptr;
	int numIn, numOut, dimension, inc, dec; 
	int i1, i2, i3, bl;
	int i,j;
	char* name = malloc(20*sizeof(char));
	char* op = malloc(20*sizeof(char));
	char* operand1 = malloc(20*sizeof(char));
	char* operand2 = malloc(20*sizeof(char));
	char* tempOut = malloc(20*sizeof(char));
	node* inputs = NULL;
	node* outputs = NULL;

	if((fptr=fopen(argv[1], "r"))==NULL){
		printf("error");
		exit(0);
	}

	//Read number of inputs
	fscanf(fptr, "INPUTVAR %d", &numIn);

	//Calculate matrix dimensions
	dimension = pow(2, numIn);

	//Add inputs to a LinkedList of inputs
	for(i=0; i < numIn;i++){
		fscanf(fptr, "%s", name);
		inputs = add(inputs, name);
	}
	fscanf(fptr, "\n");

	//Read number of outputs
	fscanf(fptr, "OUTPUTVAR %d", &numOut);

	//Add inputs to a LinkedList of outputs
	for(i=0; i < numOut;i++){
		fscanf(fptr, "%s", name);
		outputs = add(outputs, name);
	}
	fscanf(fptr, "\n");
	
	int** result = malloc(dimension*sizeof(int*));
	//Create the gray code
	if(numIn > 1){
		int* grayint=malloc(dimension*sizeof(int));
		grayint[0]=0;
		grayint[1]=1;
		grayint[2]=2;
		grayint[3]=3;
		for(i=2;i<numIn;i++){
			inc=pow(2,i);
			dec=inc-1;
			while(dec>=0){
			  grayint[inc]=grayint[dec]+pow(2,i);
			  inc++;
			  dec--;
			}
		}
		//Create the result matrix
		for(i=0;i<dimension;i++){
		  result[i]=(int*)malloc((numIn+numOut)*sizeof(int));
		}
 
		for(i=0;i<dimension;i++){
		  for(j=0;j<(numIn);j++){
		    int temp;
		    temp = bit(numIn, j, grayint[i]);
		    result[i][j]=temp;
		  }
		}
	}else{
		for(i=0;i<dimension;i++){
		  result[i]=(int*)malloc((numIn+numOut)*sizeof(int));
		}

		for(i=0;i<dimension;i++){
		  for(j=0;j<dimension;j++){
		    if(i == 1){
		    	result[i][j]=1;
		    }else{
		    	result[i][j]=0;
		    }
		  }
		}
	}
	
	
	//printMatrix(result, dimension, numIn+numOut);
	
	gateNode* gate = NULL;

	while(!feof(fptr)){
  		fscanf(fptr, "%s", op);
  		if(strcmp("NOT", op) == 0){
  			fscanf(fptr, "%s", operand1);
  			fscanf(fptr, "%s", operand2);
  			gate = addg(gate, op, operand1, operand2, operand2);
  			fscanf(fptr, "\n");
  		}
  		else if(strcmp("AND", op) == 0){
  			fscanf(fptr, " %s", operand1);
  			fscanf(fptr, " %s", operand2);
  			fscanf(fptr, " %s", tempOut);
  			gate = addg(gate, op, operand1, operand2, tempOut);
  			fscanf(fptr, "\n");
		}
		else if(strcmp("OR", op) == 0){
  			fscanf(fptr, "%s", operand1);
  			fscanf(fptr, "%s", operand2);
  			fscanf(fptr, "%s", tempOut);
  			gate = addg(gate, op, operand1, operand2, tempOut);
  			fscanf(fptr, "\n");
  		}
  		else if(strcmp("NOR", op) == 0){
  			fscanf(fptr, " %s", operand1);
  			fscanf(fptr, " %s", operand2);
  			fscanf(fptr, " %s", tempOut);
  			gate = addg(gate, op, operand1, operand2, tempOut);
  			fscanf(fptr, "\n");
  		}
  		else if(strcmp("NAND", op) == 0){
  			fscanf(fptr, " %s", operand1);
  			fscanf(fptr, " %s", operand2);
  			fscanf(fptr, " %s", tempOut);
  			gate = addg(gate, op, operand1, operand2, tempOut);
  			fscanf(fptr, "\n");
  		}
  		else if(strcmp("XOR", op) == 0){
  			fscanf(fptr, " %s", operand1);
  			fscanf(fptr, " %s", operand2);
  			fscanf(fptr, "%s", tempOut);
  			gate = addg(gate, op, operand1, operand2, tempOut);
  			fscanf(fptr, "\n");
  		}
	}
	node* temp = NULL;
	//Time for solving
	for(i = 0; i < dimension; i++){
		node* ptr = inputs;
			for(j = 0; j<numIn; j++){
				ptr->bit = result[i][j];
				ptr = ptr->next;
			}

		gateNode* ptr2 = gate;
	//So the inputs of a directive can either be an IN# or a Char
	//OR it can be a temporary variable
	//Be sure to check for both
		while(ptr2 !=NULL){
			if(strcmp("NOT", ptr2->name) == 0){
				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=not(i1);
				}else{
					i1=findint(ptr2->operand1,temp);
					i2=not(i1);
				}
				
				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i2,outputs);
				}else{
					bl=findout(ptr2->output,i2,temp);
					if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i2,temp);
					}
				}
			i1=bl;
			}else if(strcmp("AND", ptr2->name) == 0){
				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,inputs);
					i3=and(i1,i2);
				}else if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,temp);
					i3=and(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,inputs);
					i3=and(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,temp);
					i3=and(i1,i2);
				}
				
				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i3,outputs);
				}else{
					bl=findout(ptr2->output,i3,temp);
				}
				if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i3,temp);
				}
			i1=bl;
			}else if(strcmp("OR", ptr2->name) == 0){
				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,inputs);
					i3=or(i1,i2);
				}else if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,temp);
					i3=or(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,inputs);
					i3=or(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,temp);
					i3=or(i1,i2);
				}
				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i3,outputs);
				}else{
					bl=findout(ptr2->output,i3,temp);
				}if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i3,temp);
				}
			i1=bl;
			}else if(strcmp("NAND", ptr2->name) == 0){
				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,inputs);
					i3=nand(i1,i2);

				}else if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,temp);
					i3=nand(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,inputs);
					i3=nand(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,temp);
					i3=nand(i1,i2);
				}

				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i3,outputs);
				}else{
					bl=findout(ptr2->output,i3,temp);
				}
				if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i3,temp);
				}
			i1=bl;
			
			}else if(strcmp("NOR", ptr2->name) == 0){
				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,inputs);
					i3=nor(i1,i2);
				}else if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,temp);
					i3=nor(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,inputs);
					i3=nor(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,temp);
					i3=nor(i1,i2);
				}
				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i3,outputs);
				}else{
					bl=findout(ptr2->output,i3,temp);	
				}
				if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i3,temp);
				}
			i1=bl;

			}else if(strcmp("XOR", ptr2->name) == 0){

				if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,inputs);
					i3=xor(i1,i2);
				}else if(ptr2->operand1[0]>='A'&&ptr2->operand1[0]<='Z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,inputs);
					i2=findint(ptr2->operand2,temp);
					i3=xor(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='A'&&ptr2->operand2[0]<='Z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,inputs);
					i3=xor(i1,i2);
				}else if(ptr2->operand1[0]>='a'&&ptr2->operand1[0]<='z'&&ptr2->operand2[0]>='a'&&ptr2->operand2[0]<='z'){
					i1=findint(ptr2->operand1,temp);
					i2=findint(ptr2->operand2,temp);
					i3=xor(i1,i2);
				}

				if(ptr2->output[0]>='A'&&ptr2->output[0]<='Z'){
					bl=findout(ptr2->output,i3,outputs);
				}else{
					bl=findout(ptr2->output,i3,temp);
				}
				if(bl==2){
					temp=add(temp,ptr2->output);
					bl=findout(ptr2->output,i3,temp);
				}
			i1=bl;
			}
		ptr2 = ptr2->next;
		}
	ptr = outputs;
		for(int k = numIn; k<(numIn+numOut); k++){
			result[i][k] = ptr->bit;
			ptr = ptr->next;
		}
	}
	printMatrix(result,dimension, (numIn+numOut));
}
