#include <stdio.h>
#include <stdlib.h>

struct list {
    int data;
    struct list *next;
};
typedef struct list node;

void printList(node *head) {
    node *new_node = head;
    while (new_node != NULL) {
        printf("%d \n", new_node->data);
        new_node=new_node->next;
    }
}


void addEnd(node *head,int data){
    node *new_node = head;
    node *element=(node*)malloc(sizeof(node));
    element->data=data;
    element->next=NULL;


    if(new_node->next==NULL){
	new_node->next=element;
        return;
    }

    while (new_node->next!= NULL) {  
	new_node=new_node->next;
    }
    
    
    
    new_node->next=element;
}


void AFK(node *head){
   int data;
   while((scanf("%d",&data)==1) && (data!=0)){
	addEnd(head,data);
    }
while (getchar() != '\n');
printList(head);
}

int main() {
    node head;
    head.data=0;
    head.next=NULL;
    node *nod=(node*)malloc(sizeof(node));
    nod->data=1;
    nod->next=NULL;
    head.next=nod;


    printList(&head);
    addEnd(&head,5);
    printList(&head);
    AFK(&head);
    return 0;
}
