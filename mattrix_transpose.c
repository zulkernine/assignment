#include<stdio.h>
#define MAX 10
void main(){
    int n,m;
    int mattrix[MAX][MAX],transpose[MAX][MAX];
    printf("Enter the dimension m*n ");
    printf("m=");
    scanf("%d",&m);
    printf("n=");
    scanf("%d",&n); 
    printf("Enter the matrix\n");
    for(int i =1;i<=m;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mattrix[i-1][j-1]);
        }
        
    }
    for(int i =0;i<n;i++){
        for(int j=0;j<m;j++){
            transpose[i][j]=mattrix[j][i];
        }   
    }
    printf("Transpose of the given matrix is follwing:\n");
    for(int i =0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d\t",transpose[i][j]);
        }
        printf("\n\n");   
    }    
}            
    
