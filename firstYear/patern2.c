#include<stdio.h>
void main(){
    int n;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=1;i<= 2*n -1 ;i++){
        for(int k=2*(n-1)-i+1;k>0;k--){
            printf(" ");
        }
        for(int j=1;j<(i+1)/2;j++)
            printf("%d ",j);
        for(int j=(i+1)/2-i%2;j>0;j--)
            printf("%d ",j);
        printf("\n");
    }
}
