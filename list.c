
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct node
{
    
    int data;
    struct node *next;
};

struct node* head=NULL;

//adding nodes serially
void addbegin(struct node **head,int val)
{
    struct node *newnode=malloc(sizeof(struct node));
    newnode->data=val;
    newnode->next=*head;
    *head=newnode;
}


void viewlist(struct node *head)
 {
    struct node*temp=head;  
    
    #pragma omp single
    {
    while(temp!=NULL)
    {
        #pragma omp task firstprivate(temp)
        {
        printf("%d->",temp->data);
        }
        temp=temp->next;
    }
    printf("NULL\n");
    
    }
 }

int main(int *argc,char *argv[])
{
    addbegin(&head,5);
    addbegin(&head,7);
    addbegin(&head,9);
    addpar(&head,8);

    
    omp_lock_t ptrlock;
    omp_init_lock(&ptrlock);

//parallel inplementation
#pragma omp parallel
{

    void addpar(struct node **head,int val)
    {
         struct node* ptr=head;
         omp_set_lock(&ptrlock);
         struct node *newnode=malloc(sizeof(struct node));
         newnode->data=val;
         newnode->next=ptr;
         *head=newnode;
         omp_unset_lock(&ptrlock);
    }   
    

}
omp_destroy_lock(&ptrlock);

viewlist(head);
return 0;
}






    
