#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
	int data;
	char color;
	struct node *left,*right,*parent;
};

struct node *createNode(int data) {
	struct node *newNode = malloc(sizeof(struct node));
	if(!newNode) {
		printf("memory error\n");
		return NULL;
	}
	newNode->data = data;
	newNode->color = 'R';
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	return newNode;
}

bool ifUncle(struct node *child) {
	if(child->parent == NULL || child->parent == NULL || child->parent->parent == NULL || child->parent->parent->left == NULL || child->parent->parent->right == NULL) {
		return false;
	}
	return true;
}

struct node* uncle(struct node *child) {
	if (child->parent->parent->right && child->parent->parent->right != child->parent) 
		return child->parent->parent->right;
	else if (child->parent->parent->left && child->parent->parent->left != child->parent) 
		return child->parent->parent->left;
}

void inOrder(struct node *head) {
	if(head) {
		inOrder(head->left);
		printf("%d\t",head->data);
		inOrder(head->right);
	}	
}

void preOrder(struct node *head) {
	if(head) {
		printf("%d\t",head->data);
		preOrder(head->left);
		preOrder(head->right);
	}	
}

bool ifGrandParent(struct node *child) {
	if(child->parent->parent)
		return true;
	return false;
} 

struct node* grandParent(struct node *child) {
	if(ifGrandParent(child))
		return child->parent->parent;
}

struct node* root(struct node *child) {
	if(child->parent) 
		child = child->parent;
	return child;
}

void rotateLeft(struct node *Node,struct node** head) {
	struct node* parent = Node->parent;
	struct node* left = Node->left;
	struct node* right = Node->right;

	if(parent) {
		if(parent->left == Node) 
			Node->parent->left = right;
		else 
			Node->parent->right = right;
	}
	Node->right->parent = parent;
	Node->parent = right;
	Node->right = right->left;
	Node->parent->left = Node;
	if(Node->right)
		Node->right->parent = Node;

	if(!Node->parent->parent) 
		*head = Node->parent;
}

void rotateRight(struct node *Node,struct node** head ) {
	struct node* parent = Node->parent;
	struct node* left = Node->left;
	struct node* right = Node->right;

	if(parent) {
		if(parent->left == Node) 
			Node->parent->left = left;
		else 
			Node->parent->right = left;
	}	
	Node->left->parent = parent;
	Node->parent = left;
	Node->left = left->right;
	Node->parent->right = Node;
	if(Node->left)
		Node->left->parent = Node;	

	if(!Node->parent->parent) 
		*head = Node->parent;
}

void rotateLeftRight(struct node *Node,struct node **head) {
	rotateLeft(Node->parent,head);
	rotateRight(Node->parent,head);
}

void rotateRightLeft(struct node *Node,struct node **head) {
	rotateRight(Node->parent,head);
	rotateLeft(Node->parent,head);
}

void swapColor(struct node *node1,struct node *node2) {
	char temp ;
	temp = node1->color;
	node1->color = node2->color;
	node2->color = temp;
}

void inOrderColor(struct node *head) {
	if(head) {
		inOrderColor(head->left);
		printf("%c\t",head->color);
		inOrderColor(head->right);
	}	
}

struct node* violation(struct node *child,struct node **head) {
	if(!child->parent) 
		child->color = 'B';
	else if(child->color == 'R' && child->parent != NULL && child->parent->color == 'R') {
		if(ifUncle(child) && uncle(child)->color == 'R') {
			child->parent->color = 'B';
			uncle(child)->color = 'B';
			if(ifGrandParent(child) ) {
				grandParent(child)->color = 'R';
				if(grandParent(child) == *head )
					grandParent(child)->color = 'B';
			}
		}
		else {
			if(ifGrandParent(child) && grandParent(child)->left != NULL && grandParent(child)->left == child->parent) {
				if(child->parent->left != NULL && child->parent->left == child) {
					rotateRight(child->parent->parent,head);
					swapColor(child->parent,child->parent->right);
					if(child->parent->parent == NULL)
						return child->parent;

				}
				else if(child->parent->right != NULL && child->parent->right == child) {
					rotateLeftRight(child,head);
					swapColor(child->right,child);
					if(child->parent == NULL)
						return child;
				}
			}
			else if(ifGrandParent(child) && grandParent(child)->right != NULL && grandParent(child)->right == child->parent) {
				if(child->parent->left != NULL && child->parent->left == child) {
					rotateRightLeft(child,head);
					swapColor(child->left,child);
					if(child->parent == NULL)
						return child;
				}
				else if(child->parent->right != NULL && child->parent->right == child) {
					rotateLeft(child->parent->parent,head);
					swapColor(child->parent,child->parent->left);
					if(child->parent->parent == NULL) 
						return child->parent;
				}
			}
		} 
	}

}

void blackNodeRule(struct node *tempHead,struct node **head) {
	if(tempHead) {
		if(tempHead->color == 'R') {
			if(tempHead->left && tempHead->left->color == 'R') 
				*head = violation(tempHead->left,head);
			else if(tempHead->right && tempHead->right->color == 'R') 
				*head = violation(tempHead->right,head);
		}
	    blackNodeRule(tempHead->left,head);
	    blackNodeRule(tempHead->right,head);
	}

}

struct node* insert(struct node **head,int data) {
	struct node *newNode = createNode(data);
	struct node *p = *head;
	struct node *q = NULL;
	if (*head==NULL) 
		*head = newNode;
	else {
		while(p) {
			if(p->data > data && p->left != NULL) 
				p=p->left;
			else if(p->data > data && p->left == NULL) {
				p->left = newNode;
				newNode->parent = p;
				break;
			}
			else if(p->data < data && p->right != NULL) 
				p = p->right;
			else {
				p->right = newNode;
				newNode->parent = p;
				break;
			}
		}
    }
    violation(newNode,head);
    return *head;
}

void main() {
	struct node *head=NULL;
	head = insert(&head,3);
	head = insert(&head,1);
	head = insert(&head,5);
	head = insert(&head,7);
	head = insert(&head,6);
	head = insert(&head,8);
	head = insert(&head,9);
	head = insert(&head,10);

        //Another Example

	// head = insert(&head,10);
	// insert(&head,6);
	// insert(&head,14);
	// insert(&head,3);
	// insert(&head,8);
	// insert(&head,12);
	// insert(&head,16);
	// insert(&head,11);
	// insert(&head,13);
	// insert(&head,1);
	// insert(&head,4);
	// insert(&head,7);
	// insert(&head,9);
	// insert(&head,15);
	// insert(&head,17);
	
	blackNodeRule(head,&head);
	printf("After conversion into RedBlack Tree:-\n");
	printf("\n");
	inOrder(head);
	printf("\n");
	inOrderColor(head);
	printf("\n");
	preOrder(head);
	printf("\n");
}