#include<stdio.h>
int fact(int n){
    int factorial=1;
    for(int i=1;i<=n;i++)
        factorial *= i ;
    return factorial;
}
void main(){
    int n,sum=0;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        sum += fact(i) ;
    printf(" Sum =%d\n",sum);
}




