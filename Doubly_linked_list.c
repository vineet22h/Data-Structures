#include<stdio.h>
#include<stdlib.h>
struct DLLNode
{
	int data;
	struct DLLNode *next;
	struct DLLNode *prev;
};

void insert(struct DLLNode **head,int data,int position)
{
	struct DLLNode *p,*q;
	struct DLLNode *newNode = malloc(sizeof(struct DLLNode));
	int k=1;
	
	if(!newNode)
	{
		printf("Memory Error");
		return ;
	}
	newNode->data = data;
	p = *head;

	if(position == 1)
	{
		newNode->next = p;
		newNode->prev = NULL;
		if(p)
			p->prev = newNode;
		*head = newNode;
	}
	else {

		while(k < position && p != NULL)
		{	
			k++;
			q = p;
			p = p->next;
		}
		newNode->next = p;
		newNode->prev = q;
		if(p)
			p->prev = newNode;
		q->next = newNode;
	}
}


void print(struct DLLNode *head)
{
	while(head) {
		printf("%d ",head->data);
		head = head->next;
	}
}

void main()
{	
	struct DLLNode *head = NULL;
	insert(&head,1,1);
	insert(&head,3,2);
	insert(&head,2,1);
	insert(&head,5,2);	
	print(head);
}