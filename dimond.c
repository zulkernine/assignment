#include<stdio.h>
void main(){
    int n,N;
    printf("Enter a number:");
    scanf("%d",&n);
    N=2*n-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=N;j++){
            if(j>=(n-i)&&j<=(n+i))
                printf("*");
            else 
                printf(" ");
        }
        printf("\n");
    }
     for(int i=n-2;i>=0;i--){
        for(int j=0;j<N;j++){
            if(j>=(n-i)&&j<=(n+i))
                printf("*");
            else 
                printf(" ");
        }
        printf("\n");
    }
    
}
