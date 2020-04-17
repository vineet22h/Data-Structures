#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define COUNT 10

struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};
 struct stack 
{
	int top;
	int capacity;
	int* array;
};
struct stack *createStack(int capacity)
{
	struct stack *s = malloc(sizeof(struct stack));
	if(!s)
	{
	    printf("memory error");
	    return ;
    }
    s->capacity = capacity;
    s->top = -1;
    s->array = malloc(s->capacity*sizeof(int));
    return s;
}
void reSize(struct stack *s)
{
	s->capacity = s->capacity*2;
	realloc(s->array,s->capacity*sizeof(int));
}
int isFull(struct stack *s)
{
	return s->top == s->capacity;
}
int isEmpty(struct stack *s)
{
	return s->top == -1;
}
void push(struct stack *s,int data)
{
	if(isFull(s))
	{
	    printf("end");
	    return 0;
    } 
	s->array[++s->top]=data;
}
int pop(struct stack *s)
{
	if(isEmpty(s))
	{
		printf("stack is empty");
		return 0;
	}
	return s->array[s->top--];
}

struct BinaryTreeNode* createNode(int data)
{
    struct BinaryTreeNode* newNode = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    if(!newNode)
    {
        printf("memory error");
        return ;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inOrderRecursive(struct BinaryTreeNode *root)
{
    if(root)
    {
        inOrderRecursive(root->left);
        printf("%d",root->data);
        inOrderRecursive(root->right);
    }
}

void inOrderNonRecursive(struct BinaryTreeNode *root)
{
    struct stack *s = createStack(8);
    while(1)
    {
        while(root)
        {
            push(s,root);
            root = root->left;
        }
        if(isEmpty(s))
            break;
        root = pop(s);
        printf("%d",root->data);
        
        root = root->right;
    }
}
int main()
{
    int space=0;
    struct BinaryTreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    inOrderNonRecursive(root);
    return 0;
}

