#include <stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void insert(struct node **head,int data,int position)
{
    int k=1;
    struct node *p,*q,*newNode;
    newNode = malloc(sizeof(struct node));
    if(!newNode)
    {
        printf("memory error");
        return;
    }
    newNode->data = data;
    p = *head;
    
    if(position == 1)
    {
        newNode->next = p;
        *head = newNode;
    }
    else
    {
        while(p != NULL && k<position)
        {
            k++;
            q=p;
            p = p->next;
        }
        q->next = newNode;
        newNode->next = p;
    }
}

void deleteNode(struct node **head,int position)
{
    int k=1;
    struct node *p,*q;
    if(*head ==NULL)
    {
        printf("list Empty");
        return;
    }
    p = *head;
    if(position == 1)
    {
        *head = p->next;
        free(p);
        return;
    }
    else
    {
        while(p != NULL && k<position)
        {
            k++;
            q = p;
            p = p->next;
        }
        if(p==NULL)
            printf("position does not exsist");
        else
        {
            q->next = p->next;
            free(p);
        }
    }
}

void printList(struct node *head) 
{ 
  while (head != NULL) 
  { 
     printf(" %d ", head->data); 
     head = head->next; 
  } 
} 

void DeleteList(struct node **head)
{
    struct node *p,*q;
    p = *head;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *head = NULL;
}

int main() 
{ 
  
  struct node* head = NULL;
  insert(&head, 6,1); 
  insert(&head, 5,2); 
  insert(&head, 4,3);
  insert(&head,3,2);
  
  printf("\n Created Linked list is: "); 
  printList(head); 
  printf("\n");
  //deleteNode(&head,3);
  //printf("\n Created Linked list is: "); 
  //printList(head); 
  //DeleteList(&head);
    //printf("\n Created Linked list is: "); 
  //printList(head); 
  
  return 0; 
} 
