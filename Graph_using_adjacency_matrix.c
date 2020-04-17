
#include <stdio.h> 
#include <stdlib.h> 
  
int main() 
{ 
    int v, i, j, count; 
    printf("Enter number of vertices :");
    scanf("\t%d",&v);
    int **matrix = (int **)malloc(v * sizeof(int *)); 
    for (i=0; i<v; i++) 
         matrix[i] = (int *)malloc(v * sizeof(int)); 
  
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    count = 0; 
    for (i = 0; i <  v; i++) 
    {
      for (j = 0; j < v; j++) 
      {
         int a=0;
         printf("is there connection between %d to %d :",i,j);
         scanf("\t%d",&a);
         matrix[i][j] = a; 
      }
    }// OR *(*(arr+i)+j) = ++count 
  
    for (i = 0; i <  v; i++) 
    {
      for (j = 0; j < v; j++) 
      {
         printf("%d\t ", matrix[i][j]);  
      }
      printf("\n");
    }
         
         
  
   /* Code for further processing and free the  
      dynamically allocated memory */
  
   return 0; 
} 