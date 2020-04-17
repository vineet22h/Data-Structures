#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *left,*right;
    int data;
    int LThread;
    int RThread;
};

struct node* insert(struct node *root,int data)
{
    struct node *ptr = root;
    struct node *par = NULL;
    while(ptr)
    {
        if(ptr->data == data)
        {
            printf("Duplicate");
            return ;
        }
        par = ptr;
        
        if (ptr->data >data)
        {
            if (ptr->LThread == 0)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->RThread == 0)
                ptr = ptr->right;
            else
                break;
        }    
    }
    struct node *tmp = malloc(sizeof(struct node));
    
    tmp->LThread =1;
    tmp->RThread = 1;
    tmp->data = data;
    if (ptr == NULL)
    {
        root = tmp;
        tmp->left = NULL;
        tmp->right = NULL;
    }
    else if(data > par->data)
    {
        tmp->right = par->right;
        tmp->left = par;
        par->RThread = 0;
        par->right = tmp;
    }
    else if(data < par->data)
    {
       tmp->left = par->left;
       tmp->right = par;
       par->LThread = 0;
       par->left = tmp;
   }    
  
    return root;
}

struct node *inOrderSuccessor(struct node *root)
{
    if(root->RThread == 1)
        return root->right;

    root = root->right;
    while(root->LThread == 0)
        root = root->left;
    return root;
}

void inorder(struct node *root)
{
    if(!root)
    {
        printf("Tree is Empty");
        return;
    }
    
    while(root->LThread == 0)
        root = root->left;
    
    while(root)
    {
        printf("%d\t",root->data);
        root = inOrderSuccessor(root);
    }
}
struct node *caseC(struct node *root,struct node *par,struct node *ptr)
{
    struct node *tmp = ptr;
    struct node *parch;
    if(!par)
        root = NULL;
    tmp = tmp->right;
    while(tmp)
    {
        parch = tmp;
        tmp = tmp->left;
    }
    ptr->data = tmp->data;
    if(parch == )
    free(tmp);
    return root;
}
struct node *Delete(struct node *root,int data)
{
    struct node *ptr = root;
    struct node *par = NULL;
    int found = 0;
    if(!ptr)
        return ;
        
    while(ptr)
    {
        if (ptr->data == data)
        {
            found = 1;
            break;
        }
        else if(ptr->data > data)
        {
            if(ptr->LThread == 0)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if(ptr->RThread == 0)
                ptr = ptr->right;
            else
                break;
        }
        par = ptr;
    }
    if (found == 0)
    {
        printf("Element is not present");
        return;
    }
    if (ptr->LThread == 0 && ptr->RThread == 0)
        root = caseC(root,par,ptr);
    else if(ptr->LThread == 0)
        root = caseB(root,par,ptr);
    else if(ptr->RThread == 0)
        root = caseB(root,par,ptr);
    else
        root = caseA(root,par,ptr);
    
    return root;   
    }
void main()
{
    struct Node *root = NULL; 
  
    root = insert(root, 20); 
    root = insert(root, 10); 
    root = insert(root, 30); 
    root = insert(root, 5); 
    root = insert(root, 16); 
    root = insert(root, 14); 
    root = insert(root, 17); 
    root = insert(root, 13); 
  
    inorder(root); 
    
    
}