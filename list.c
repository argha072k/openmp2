#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct node
{
    int data;
    struct node *next;
    omp_lock_t lock;
};

struct node* head=NULL;


void addserial(struct node** head,int data)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=*head;
    *head=newnode;
   
}

void addparallel(struct node** head,int data)
{
 struct node* ptr=*head;
   
  #pragma omp parallel num_threads(8)
  {
    omp_init_lock(&ptr->lock);  
   
    omp_set_lock(&ptr->lock);
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=ptr;
    *head=newnode;
    omp_unset_lock(&ptr->lock); 

  }
omp_destroy_lock(&ptr->lock);


}


void viewlist(struct node *temp)
 {
    #pragma omp single
    {
    while(temp!=NULL)
    {
     #pragma omp task firstprivate(temp)
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
    
    }
 }

int main(int *argc,char *argv[])
{
    addserial(&head,5);
    addserial(&head,7);
    addserial(&head,9);
    addserial(&head,11);
    addparallel(&head,40);
    addparallel(&head,55);
    addparallel(&head,85);
    
    

viewlist(head);

return 0;
}


// output : 85->55->40->11->9->7->5->NULL 





    
