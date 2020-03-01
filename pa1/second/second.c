#include <stdlib.h>
#include <stdio.h>

typedef struct node {
        int data;
        struct node *nextptr;
}Node;
void insertBetween(Node *curr, int data){
        Node *ptr= (Node *) malloc(sizeof(Node));
        ptr->data=data;
        ptr->nextptr= curr->nextptr;
        curr->nextptr = ptr;
}

void insertEnd(Node *curr, int data){
        Node *ptr= (Node *) malloc(sizeof(Node));
        ptr->data=data;
        ptr->nextptr= NULL;
        curr->nextptr = ptr;
}


int main(int argc, char *argv[]){
        char command;
        int num;
        Node *ptr,*head;
        FILE *rfptr;
        if ((rfptr=fopen(argv[1],"r"))==NULL)
        {
		printf("error"); 
		exit(0);
	}

        ptr= (Node *) malloc(sizeof(Node));
        ptr->nextptr=NULL;
        head=ptr;
        fscanf(rfptr,"%c\t%d\n",&command,&num);
        
        while( command=='d') {
                fscanf(rfptr,"%c\t%d\n",&command,&num);
                if(command=='\0') {
                        printf("0");
                        return 0;
                }
                if(feof(rfptr)){
                  printf("0");
                  return 0;
                }
        }
        if(command=='i') {

                // ptr= (Node *) malloc(sizeof(Node));
                //  ptr->nextptr=NULL;
                ptr->data=num;

                //head=ptr;
        }
        else{
                return 0;
        }
        while(!feof(rfptr)) {
                // fscanf(rfptr,"%c\t&",&command, &num);
                fscanf(rfptr,"%c\t%d\n",&command,&num);
                //printf("head's data %d\n", head->data);
                if(command=='i') {
                        ptr= (Node *) malloc(sizeof(Node));
                        ptr->data=num;
                        if(head==NULL) {
                                ptr->nextptr=NULL;
                                head = ptr;
                                continue;
                        }
                        if(num<=head->data) {
                                ptr->nextptr=head;
                                head=ptr;
                        }
                        else{
                                Node *temp,*nptr;
                                for(temp = head; temp->nextptr!=NULL; temp = temp->nextptr) {
                                        nptr = temp->nextptr;
                                        if(num>=temp->data && num<nptr->data) {
                                                //printf("Im here!");
                                                insertBetween(temp,num);
                                                break;
                                        }

                                }
                                if(num>=temp->data && temp->nextptr==NULL) {
                                        insertEnd(temp,num);
                                }
                        }
                }else if(command == 'd') {
                        if(head->data == num) {
                                head = (head->nextptr==NULL) ? NULL : head->nextptr;
                        }else{
                                Node *temp,*nptr;
                                for(temp = head; temp->nextptr!=NULL; temp = temp->nextptr) {
                                        nptr = temp->nextptr;
                                        if(nptr->data == num) {
                                                temp->nextptr = (nptr->nextptr==NULL) ? NULL : nptr->nextptr;
                                                break;
                                        }
                                }
                        }
                }


        }

        Node *current = head;
        int counter = 0;
        while(current != NULL) {
                counter++;
                current = current->nextptr;
        }

        printf("%d\n", counter);
        current = head;
        while(current!=NULL) {
                while(current->nextptr!= NULL && (current->nextptr)->data==current->data) {
                        current= current->nextptr;
                }
                printf("%d\t", current->data);
                current= current->nextptr;
                // while(current->nextptr!= NULL && (current->nextptr)->data == current->data){
                //   current = current->nextptr;
                // }
        }
        //printf("\n");


        return 0;
}
