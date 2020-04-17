#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
	int* keys;
	int n;
	bool leaf;
	struct Node** child;
	int order;
	
};

struct set {
	struct Node *root;
	int index;
};

struct Node *createNode(int order) {
	struct Node *node = malloc(sizeof(struct Node));
	if(!node) {
		printf("memory error");
		return NULL;
	}
	node->leaf = true;
	node->n = 0;
	node->keys = malloc(sizeof(int)*(2*order-1));
	node->child = malloc(sizeof(struct Node**)*(2*order));
	node->order = order;
	return node;
}

struct Node* split(int j ,struct Node *node,struct Node *parent) {
	int order = node->order;
	struct Node *sibling = createNode(node->order);
	sibling->leaf = node->leaf;
	sibling->n = order -1;

	for(int i = 0;i<order-1;i++)
		sibling->keys[i] = node->keys[i+order];
    
	if(node->leaf) {
		for(int i = 0;i<order;i++)
			sibling->child[i] = node->child[i+order];
	}
	node->n = order-1;
  
	for(int i = parent->n;i >= j+1;i--)
		parent->child[i+1] = parent->child[i];
	
	parent->child[j+1] = sibling;

	for(int i = parent->n-1;i>=j;i--)
		parent->keys[i+1] = parent->keys[i];
	parent->keys[j] = node->keys[order-1];
	
	parent->n+=1;
	return parent;
}

struct Node* insertNonFull(struct Node *head,int data) {
	int index = head->n;
	int order = head->order;
	if(head->leaf) {
		int i = index;
		while(i>=0 && head->keys[i-1] > data) {
			head->keys[i] = head->keys[i-1];
			i--;
		}

		head->keys[i] = data;
		head->n+=1;
		
	}
	else {
		while(index>0 && head->keys[index-1] > data) 
			index--;

		if(head->child[index]->n == 2*order-1) {
			head = split(index,head->child[index],head);
			if(head->keys[index] < data)
				index++;
		}
	    insertNonFull(head->child[index],data);

	}
	return head;
}

struct set* search(struct Node *head,int data) {
 	int i=0;
 	while (i <= head->n && data > head->keys[i]) {
 		i++;
 	}
 
 	if (i <= head->n && data == head->keys[i]) {
 		struct set* r = malloc(sizeof(struct set));
 		r->root = head;
 		r->index = i;
 		return r;
 	}
 	else if(head->n == i-1) 
 		return search(head->child[head->n],data);
 	else if(head->n == 2*head->order-1) {
 		printf("element not present\n");
 		struct set* r = malloc(sizeof(struct set));
	 	r->root = head;
	 	r->index = -1;
	 	return r;
 	}
 	else
 		return search(head->child[i],data);
 }

struct Node* insert(struct Node *root,int data) {
	int order = root->order;
	if(root->n == 0) {
		root->keys[0] = data;
		root->n+=1;
		return root;
	}
	else {
		if(root->n == 2*order-1) {
			struct Node *parent = createNode(order);
			parent->leaf = false;
			parent->child[0] = root;
			parent = split(0,root,parent);		
			int i = 0;
			if(parent->keys[0] < data)
				i++;
			parent->child[i] = insertNonFull(parent->child[i],data);
			return parent;
		}
		else 
			return insertNonFull(root,data);
	}
}

void traverse(struct Node *head) {
	for(int i=0;i<=head->n;i++) {
		if(head->leaf) {
			for(int j = 0;j < head->n;j++)
				printf("%d ",head->keys[j]);
			return;
		}
		else
			traverse(head->child[i]);
		if(i != head->n)
			printf("%d ",head->keys[i]);
	}
	printf("\n");
}
void main() {
	struct Node *head = createNode(2);
	head = insert(head,1);
	head = insert(head,6);
	head = insert(head,5);
	head = insert(head,8);
	head = insert(head,4);
	head = insert(head,3);
	head = insert(head,2);
	head = insert(head,9);
  
	traverse(head);

	struct set *elem = NULL;
	elem = search(head,1);
  	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
  	
	elem = search(head,2);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);   
	
	elem = search(head,3);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
        
	elem = search(head,4);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);    
	
	elem = search(head,5);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
        
	elem = search(head,6);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
        
	elem = search(head,8);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);   
	
	elem = search(head,9);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
  
	// element not present address is dummy can avoided using index =- 1
	elem = search(head,7);
	printf("root address is %p and index is %d and element is %d\n",elem->root,elem->index,elem->root->keys[elem->index]);
}