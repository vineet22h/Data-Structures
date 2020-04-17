#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define SPACE 20

struct AVLTreeNode {
	int data;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
	int height;
};

int max(int a,int b) {
	return (a>b)? a:b;
}

int height(struct AVLTreeNode *n) {
	if(n == NULL)
		return 0;
	return n->height;
}

struct AVLTreeNode *newNode(int data) {
	struct AVLTreeNode* node = malloc(sizeof(struct AVLTreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

struct AVLTreeNode *SingleRotateRight(struct AVLTreeNode *x) {
	struct AVLTreeNode *w = x->left;
	x->left = w->right;
	w->right = x;
	x->height = max(height(x->left),height(x->right))+1;
	w->height = max(height(w->left),height(w->right))+1;
	return w;
}

struct AVLTreeNode *SingleRotateLeft(struct AVLTreeNode *w) {
	struct AVLTreeNode *x = w->right;
	w->right = x->left;
	x->left = w;
	w->height = max(height(w->left),height(w->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	return x; 
}

struct AVLTreeNode *RotateLeftRight(struct AVLTreeNode *z) {
	z->left = SingleRotateLeft(z->left);
	return SingleRotateRight(z);
}

struct AVLTreeNode *RotateRightLeft(struct AVLTreeNode *z) {
	z->right = SingleRotateRight(z->right);
	return SingleRotateLeft(z);
}

int getBalance(struct AVLTreeNode *root) {
	return (height(root->left)-height(root->right));
}

struct AVLTreeNode* insert(struct AVLTreeNode *root,int data) {
	if (root == NULL)  
        return(newNode(data));  
  
    if (data < root->data)  
        root->left = insert(root->left, data);  
    else if (data > root->data)  
        root->right = insert(root->right, data);  
    else  
        return root;  
  	
    root->height = 1 + max(height(root->left),height(root->right));  
    int balance = getBalance(root);  
    //1) data > root->left->data 
    //2) data < root->left->data
    //3) data > root->right->data
    //4) data < root->right->data
    // this condition is used to check whether the new node is inserted in left or right of parent

    // Left Left Case  
    if (balance > 1 && data < root->left->data) {
    	// printf("right");
        return SingleRotateRight(root);  
    }
  
    // Right Right Case  
    if (balance < -1 && data > root->right->data) {
    	// printf("left\n");
    	return SingleRotateLeft(root);  
    } 
       
    // Left Right Case 
    if (balance > 1 && data > root->left->data) { 
    	// printf("LEFT RIGHT\n");
        return RotateLeftRight(root);
    }
  
    // Right Left Case  
    if (balance < -1 && data < root->right->data) {
    	// printf("right left\n");
        return RotateRightLeft(root);
    }
  
    return root;  
}  
  
void preOrder(struct AVLTreeNode *root) {  
    if(root) { 
        printf("%d\t",root->data);  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
    printf("\n");
}  

void inOrder2DPrinting(struct AVLTreeNode *root,int space) {
	if(root) {	
		space+=SPACE;
		inOrder2DPrinting(root->right,space);
		
		for(int i=0;i<space;i++)
			printf(" ");
		printf("%d\n\n",root->data);
		inOrder2DPrinting(root->left,space);
	}
}

int main()   {  
    struct AVLTreeNode *root = NULL; 
    root = insert(root, 1);  
    root = insert(root, 2);  
    root = insert(root, 3);  
    root = insert(root, 4);  
    root = insert(root, 8);  
    root = insert(root, 5);  
  
    int space = 0;
    printf("constructed AVL tree in 2D is :- \n");  
    inOrder2DPrinting(root,space);  
    // preOrder(root);  
    return 0;  
}  