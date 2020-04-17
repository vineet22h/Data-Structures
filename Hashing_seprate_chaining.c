#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define  LOAD_FACTOR 20

struct ListNode 
{
    int key;
    int data;
    struct ListNode *next;
};
struct HashTableNode
{
    int bcount;
    struct ListNode *next;
};
struct HashTable
{
    int size;
    int count;
    struct HashTable **Table;
};
struct HashTable *CreateHashTable(int size)
{
    struct HashTable *h;
    h =(struct HashTable*)malloc(sizeof(struct HashTable));
    if(!h)
        return NULL;
    h->tsize = size/LOAD_FACTOR;
    h->count = 0;
    h->Table = (struct HashTableNode**)malloc(sizeof(struct HashTableNode*)*h->size);
    if(!h->Table)
    {
        printf("Memory error");
        return NULL;
    }
    for(int i=0;i<h->tsize;i++)
    {
        h->Table[i]->next = NULL;
        h->Tabel[i]->count = 0;
    }
    return h;
}
int HashSearch(struct HashTable *h,int data)
{
    struct ListNode *temp;
    temp = h->Table[Hash(data,h->tsize)]->next;
    while(temp)
    {
        if(temp->data == data)
            return 1;
        temp = temp->next;
    }
    return 0;
}
int HashInsert(struct HashTable *h,int data)
{
    int index;
    struct ListNode *temp ,*newNode;
    if(HashSearch(h,data))
        return 0;
    index = Hash(data,h->tsize);
    temp = h->Table[index]->next;
    newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(!newNode)
    {
        printf("out of space");
        return -1;
    }
    newNode->key = index;
    newNode->data = data;
    newNode->next = h->Table[index]->next;
    h->Table[index]->next = newNode;
    h->Table[index]->bcount++;
    h->count++;
    if(h->Count/h->tsize > LOAD_FACTOR)
        rehash(h);
    return 1;
}
int HashDelete(struct HashTable *h,int data)
{
    int index;
    struct ListNode *temp,*prev;
    index = Hash(data,h->tsize);
    for(temp = h->Table[index]->next,prev = NULL;temp;prev = temp,temp = temp->next)
    {
        if(temp->data==data)
        {
            if(prev!=NULL)
                prev->next = temp->next;
            free(temp);
            h->Table[index]->bcount--;
            h->count--;
            return 1;
        }
    }
    return 0;
}
void Rehash(struct HashTable *h)
{
    int oldsize,i,index;
    struct ListNode *p,*temp,*temp2;
    struct HashTableNode **oldTable;
    oldsize = h->tsize;
    oldTable = h->Table;
    h->tsize = h->tsize*2;
    h->Table = (struct HashTableNode**)malloc(h->tsize*sizeof(struct HashTableNode*));
    if(!h->Table)
    {
        printf("Allocation failed");
        return ;
    }
    for(int i=0;i<oldsize;i++)
    {
        for(temp = oldTable[i]->next;temp;temp = temp->next)
        {
            index = Hash(temp->data,h->tsize);
            temp2 = temp;
            temp = temp->next;
            temp2->next = h->Table[index]->next;
            h->Table[index]->next = temp2;
        }
    }
}    
int main()
{
    printf("Hello World");

    return 0;
}