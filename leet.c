#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val;
    struct Node *next; 
};

int main(){
    struct Node *newnode=malloc(sizeof(struct Node));
    struct Node *one= malloc(sizeof(struct Node));
  


    newnode->val=10;
    newnode->next= one;
    one->val=20;
    newnode->next= NULL;



    struct Node* current = newnode;

    while (current->next!= NULL) {
    printf("%d ", current->val);
    current->next=current->next;
}
}