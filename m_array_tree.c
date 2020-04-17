#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct list {
	int data;
	struct list *next;
};

struct node {
	int data;
	struct node *nextSibling;
	struct node *child;
	struct list *link;
};

struct node* createNode(int data) {
	struct node *treeNode = malloc(sizeof(struct node));
	if(!treeNode) {
		printf("memory error\n");
		return NULL;
	}
	treeNode->data = data;
	treeNode->nextSibling = NULL;
	treeNode->child = NULL;
	return treeNode;
}

struct list* createList(int data) {
	struct list *listNode = malloc(sizeof(struct list));
	if(!listNode) {
		printf("memory error\n");
		return NULL;
	}
	listNode->data = data;
	listNode->next = NULL;
	return listNode;
}

struct list* insertItemList(struct list **head,int data) {
	struct list *listNode = createList(sizeof(struct list));
	struct list *p = *head;
	if(!listNode) {
		printf("memory error\n");
		return NULL;
	}
	listNode->data = data;
	if(*head  == NULL)
		*head = listNode;
	else {
		while(p->next) 
			p = p->next;
		p->next = listNode;
	}

	listNode->next = NULL;

	return *head;
}

void printList(struct list *root) {
	while(root) {
		printf("%d\t",root->data);
		root = root->next;
	}
	printf("\n");
}
void main() {
	struct list *head1 = NULL;
	struct list *head2 = NULL;
	struct list *head3 = NULL;
	struct node *root = createNode(5);
	root->child = createNode(2);
	root->child->nextSibling = createNode(4);
	root->child->nextSibling->nextSibling = createNode(3);


	head1 = insertItemList(&head1,10);
	insertItemList(&head1,20);
	insertItemList(&head1,30);
	insertItemList(&head1,40);
	
	head2 = insertItemList(&head2,50);
	insertItemList(&head2,60);
	insertItemList(&head2,70);
	insertItemList(&head2,80);

	head3 = insertItemList(&head3,90);
	insertItemList(&head3,100);
	insertItemList(&head3,110);
	insertItemList(&head3,120);


	root->child->link = head1;
	root->child->nextSibling->link = head2;
	root->child->nextSibling->nextSibling->link = head3;

	printf("%d : ",root->child->data);
	printList(root->child->link);
	printf("%d : ",root->child->nextSibling->data);
	printList(root->child->nextSibling->link);
	printf("%d : ",root->child->nextSibling->nextSibling->data);
	printList(root->child->nextSibling->nextSibling->link);
	
}