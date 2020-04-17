#include<stdio.h>
#include<stdlib.h>

struct ListNode
{
    int dest;
    struct ListNode* next;
};

struct List
{
    struct ListNode* head;
};

struct Graph
{
    int v;
    struct List* array;
};

struct Graph *createGraph(int v)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->v = v;
    graph->array = malloc(sizeof(struct List)*v);
    
    for(int i=0;i<v;i++)
    {
        graph->array[i].head = NULL;
    }
    return graph;
}

struct ListNode *createListNode(int dest)
{
    struct ListNode *lst = malloc(sizeof(struct ListNode));
    lst->dest = dest;
    lst->next = NULL;
    return lst;
}

void addEdge(struct Graph* graph,int src,int dest)
{
    struct ListNode *node = createListNode(dest);
    node->next = graph->array[src].head;
    graph->array[src].head = node;
    
    node = createListNode(src);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
    
}

void printGraph(struct Graph* graph) 
{
    for (int v = 0; v < graph->v; ++v) 
    { 
        struct ListNode* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of  \n vertex %d", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 
Q
void main()
{
    int V = 5; 
    struct Graph* graph = createGraph(V); 
    addEdge(graph, 0, 1); 
    addEdge(graph, 0, 4); 
    addEdge(graph, 1, 2); 
    addEdge(graph, 1, 3); 
    addEdge(graph, 1, 4); 
    addEdge(graph, 2, 3); 
    addEdge(graph, 3, 4); 
  
    // print the adjacency list representation of the above graph 
    printGraph(graph); 
}