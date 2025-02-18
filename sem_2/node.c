#include <stdio.h>
#include <stdlib.h>

struct list{
int data;
struct list *next=NULL;
};

typedef struct list node;

int printList(node head){
  node new_node=head;
  while(new_node->next !=NULL){
  	printf("%d \n",new_node.data);
  	new_node=new_node->next;
  } 
}



int main(){

node head;
node nod{
int data=1;
node next=NULL;
}


}
