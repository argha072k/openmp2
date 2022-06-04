
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct node
{
    
    int data;
    struct node *next;
};

struct node* head=NULL;

#pragma omp parallel num_threads (4)

{
#pragma omp task
void addbegin(struct node **head,int val)
{
    struct node *newnode=malloc(sizeof(struct node));
    newnode->data=val;
    newnode->next=*head;
    *head=newnode;
}
#pragma omp single
void print(struct node *head)
{
    struct node*temp=head;
    
    {
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
    }
}
}

int main(int *argc,char *argv[])
{
    addbegin(&head,5);
    addbegin(&head,7);
    addbegin(&head,9);
    print(head);
    return 0;
}