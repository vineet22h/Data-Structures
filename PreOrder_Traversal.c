#include<stdio.h>
#include<stdlib.h>
#define COUNT 20
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

void preOrder(struct node *tmp)
{
   if(tmp)
    {
        printf("%d\t%u\n",tmp->data,tmp);
        preOrder(tmp->left);
        preOrder(tmp->right);
    }
}

struct node *createNode(int data)
{
    struct node *Node = malloc(sizeof(struct node));
    if(!Node)
    {
        printf("Memory error");
        return 0;
    }
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    
    return Node;
}

struct node *insert(struct node *root,int data)
{
    if(root == NULL)
    {
        return createNode(data);
        //printf("first  %d\t%u\n",root->data,root);
    }
    else
    {
        if(root->data > data)
        {
            root->left = insert(root->left,data);
            //printf("left  %d\t%u\n",root->left->data,root->left);
        }
        else if(root->data <data)
        {
            root->right = insert(root->right,data);
            //printf("right  %d\t%u\n",root->right->data,root->right);
        }
    }
    return root;
}
void preOrder_2DPrinting(struct node *root,int space)
{
    if(root)
    {
        space += COUNT;
        preOrder_2DPrinting(root->right,space);

        for(int i=0 ;i<space;i++)
            printf(" ");
        printf("%d\n",root->data);
        preOrder_2DPrinting(root->left,space);
    }
}

struct node* search(struct node *root,int data)
{
    if(root==NULL)
    {
        printf("Elment not found");
        return 0;
    }
    else
    {
        if (root->data == data)
            return root;
        else if(root->data >data)
            return search(root->left,data);
        else
            return search(root->right,data);
    }
}
struct node* findMax(struct node* root) 
{ 
   if(root == NULL)
        return NULL;
    else if(root->right == NULL)
        return root;
    else 
        return findMax(root->right);
} 

struct node* delete(struct node *root,int data)
{
    struct node *tmp = NULL;
    
    if(root==NULL)
        printf("Elment not found\n");
    else if(root->data > data)
        root->left = delete(root->left,data);
    else if (root->data < data)
        root->right = delete(root->right,data);
    else if(root->data == data)
    {
        printf("\n\t%u\n",root);
        if(root->left && root->right)
        {
            tmp = findMax(root->left);
            root->data = tmp->data;
            root->left = delete(root->left,root->data);
        }
        else 
        {
           if (root->left == NULL) 
        { 
            struct node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            struct node *temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct node* temp = minValueNode(root->right); 
  
        // Copy the inorder successor's content to this node 
        root->data = temp->data; 
  
        // Delete the inorder successor 
        root->right = deleteNode(root->right, temp->data); 
        }
    }
   return root;
}

struct node * minValueNode(struct node* node) 
{ 
    struct node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct node* deleteNode(struct node* root, int data) 
{ 
    // base case 
    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (data < root->data) 
        root->left = deleteNode(root->left, data); 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (data > root->data) 
        root->right = deleteNode(root->right, data); 
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        // node with only one child or no child 
        if (root->left == NULL) 
        { 
            struct node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            struct node *temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct node* temp = minValueNode(root->right); 
  
        // Copy the inorder successor's content to this node 
        root->data = temp->data; 
  
        // Delete the inorder successor 
        root->right = deleteNode(root->right, temp->data); 
    } 
    return root; 
} 
void main()
{
    struct node* root = NULL;
    struct node* tmp  = NULL;
    root = insert(root,5);
    insert(root,3);
    insert(root,4);
    insert(root,2);
    insert(root,6);
    
    preOrder(root);
    tmp = search(root,6);
    printf("\n%u\n",tmp);
    root = deleteNode(root,5);
    preOrder(root);
    preOrder_2DPrinting(root,0);
    
}
