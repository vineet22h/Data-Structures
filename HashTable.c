#include<stdio.h>
#include<stdlib.h>
struct ListNode {
	int data;
	int key;
	struct ListNode *next;
};

struct HashTableNode {
	int bcount;
	struct ListNode *next;
};

struct HashTable {
	int tsize;
	int count;
	struct HashTableNode **table;
};

int hash(int data,int size) {
	return (data % size);
}

struct HashTable *createHashTable(int size) {
	struct HashTable *h = malloc(sizeof(struct HashTable));
	if(!h) {
		printf("memory error\n");
		return NULL;
	}
	h->tsize = size;
	h->count = 0;
	h->table = malloc(sizeof(struct HashTableNode**)*h->tsize);
	if(!h->table) {
		printf("memory error in arr\n");
		return NULL;
	}
	for(int i = 0;i < h->tsize;i++) {
		h->table[i] = malloc(sizeof(struct HashTableNode*));
		h->table[i]->next = NULL;
		h->table[i]->bcount = 0;
		
	}
	return h;
}

int hashSearch(struct HashTable *h,int data) {
	struct ListNode *temp;
	
	temp = h->table[hash(data,h->tsize)]->next;
	while(temp) {
		if(temp->data == data)
			return 1;
		temp = temp->next;
	}
	return 0;
}

int HashInsert(struct HashTable *h,int data) {
	int index;
	struct ListNode *temp,*newNode;
	if(hashSearch(h,data))
		return 0;
	index = hash(data,h->tsize);
	temp = h->table[index]->next;
	newNode = malloc(sizeof(struct ListNode));
	if(!newNode) {
		printf("memory error\n");
		return -1;
	}
	newNode->key = index;
	newNode->data = data;
	newNode->next = h->table[index]->next;
	h->table[index]->next = newNode;
	h->table[index]->bcount++;
	// printf("%d\n",index );
	h->count++;
	return 1;
}

void reHash(struct HashTable *h) {
	int oldSize,i,index;
	struct ListNode *p,*temp,*temp2;
	struct HashTableNode **oldTable;
	oldSize = h->tsize;
	oldTable = h->table;
	h->tsize *=2;
	h->table = malloc(sizeof(struct HashTableNode**)*h->tsize);
	if(!h->table) {
		printf("memory problem\n");
		return;
	}
	
	for(int i=0;i<h->tsize;i++)
		h->table[i] = malloc(sizeof(struct HashTableNode*));
	
	for(int i=0;i<oldSize;i++) {
		// printf("%d %d %d\n",oldTable[i]->next );
		// printf("%d\n",i );
		for(temp = oldTable[i]->next;temp;) {
			index = hash(temp->data,h->tsize);
			temp2 = temp;
			temp = temp->next;
			temp2->next = h->table[index]->next;
			h->table[index]->next = temp2;
			printf("in\n");
		}
	}
}

void main() {
	struct HashTable *h = createHashTable(5);
	printf("%d\n",h->tsize);
	printf("%d\n",HashInsert(h,5));
	printf("%d\n",HashInsert(h,15));
	printf("%d\n",HashInsert(h,3));

	printf("%d %d\n",h->table[0]->next->data ,h->table[0]->next->next->data);
	printf("%d\n",h->table[0]->bcount);

	reHash(h);
	printf("%d\n",hashSearch(h,15));
	printf("%d\n",hashSearch(h,5));
	printf("%d\n",hashSearch(h,3));
}