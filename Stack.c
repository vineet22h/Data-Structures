#include<stdio.h>
#include<stdlib.h>>
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
void main()
{
   	struct stack *s = createStack(1);
   	push(s,10);
   	push(s,20);
   	push(s,30);
   	printf("%d\n",pop(s));
   	printf("%d\n",pop(s));
   	printf("%d\n",pop(s));
   	// s->array[3]=10;
   	printf("%d",s->array[3]);
}