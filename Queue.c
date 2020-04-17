#include <stdio.h>
#include<stdlib.h>
struct Queue
{
    int rear;
    int front;
    int capacity;
    int* array;
};
struct Queue *createQueue(int capacity)
{
    struct Queue *Q = malloc(sizeof(struct Queue));
    if(!Q)
        printf("memory error");
    Q->rear = Q->front = -1;
    Q->capacity = capacity;
    Q->array = malloc(Q->capacity*sizeof(int));
    
    return Q;
}
int isFull(struct Queue *Q)
{
    return Q->front == Q->capacity-1;
}
int isEmpty(struct Queue *Q)
{
    return Q->front == -1;
}
void EnQueue(struct Queue *Q,int data)
{
    if(isFull(Q))
        return ;
    Q->array[++Q->front] = data;
}
int DeQueue(struct Queue *Q)
{
    if(isEmpty(Q))
        return ;
    return Q->array[++Q->rear];
}
void main()
{
    struct Queue *Q = createQueue(3);
    EnQueue(Q,10);
    EnQueue(Q,20);
    EnQueue(Q,30);
    printf("%d\n",DeQueue(Q));
    printf("%d\n",DeQueue(Q));
    printf("%d\n",DeQueue(Q));
}