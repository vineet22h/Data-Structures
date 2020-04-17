
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
    return (Q->rear+1)%Q->capacity == Q->front;
}
int isEmpty(struct Queue *Q)
{
    return Q->front == -1;
}
void EnQueue(struct Queue *Q,int data)
{
    if(isFull(Q))
    {
        printf("Queue is full\n");
        return ;
    }
    else if(Q->front == -1)
    {
        Q->rear = 0;
        Q->front =0;
        Q->array[Q->rear] = data;
    }
    else
    {
        Q->rear = (Q->rear+1)%Q->capacity;
        Q->array[Q->rear] = data;
    }
}
int DeQueue(struct Queue *Q)
{
    int temp;
    if(isEmpty(Q))
    {
        printf("Queue is empty\n");
        return ;    
    }
    else if(Q->front == Q->rear)
    {
        temp = Q->array[Q->front];
        Q->front = Q->rear = -1;
        return temp;
    }
    else
    {
        temp = Q->array[Q->front];
        Q->front = (Q->front+1)%Q->capacity;
        return temp;
    }
        
    }
void main()
{
    struct Queue *Q = createQueue(3);
    EnQueue(Q,10);
    EnQueue(Q,20);
    EnQueue(Q,30);
   
    printf("%d\n",DeQueue(Q));
    EnQueue(Q,10);
    printf("%d\n",DeQueue(Q));
    printf("%d\n",DeQueue(Q));
    printf("%d\n",DeQueue(Q));
}

