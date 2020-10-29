#include<stdio.h>
#include<stdlib.h>
void swap(int*m,int*n){
    int t;
    t=*m;
    *m=*n;
    *n=t;
}
void main(){
    int **mat,n;
    printf("Enter the dimension of n*n mattrix. n= ");
    scanf("%d",&n);
    mat=(int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)    
        *(mat+i)=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",(*(mat+i)+j));
    //swapping
    printf("swapped matrix is following:\n");
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            swap((*(mat+i)+j),(*(mat+j)+i));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%d ",*(*(mat+i)+j));
        printf("\n");
    }
}
            
    
