#include<stdio.h>
#include<stdlib.h>
#define SPACE 20

struct Node {
	int data;
	struct Node *left;
	struct Node *right;
};

struct Node *createNode(int data) {
	struct Node *newNode = malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void inOrder2DPrinting(struct Node *root,int space) {
	if(root) {	
		space+=SPACE;
		inOrder2DPrinting(root->right,space);
		
		for(int i=0;i<space;i++)
			printf(" ");
		printf("%d\n\n",root->data);
		inOrder2DPrinting(root->left,space);
	}
}

void main() {
	struct Node *head = createNode(10);
	head->left = createNode(5);
	head->right = createNode(15);
	head->left->right = createNode(2);
	head->left->left = createNode(3);
	head->right->left = createNode(14);


	inOrder2DPrinting(head,0);

}