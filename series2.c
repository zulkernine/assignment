#include<stdio.h>
int f(int n){
    int sum=0;
    for(int i=1; i<=n;i++){
        if(n%i==0)
            sum += i;
    }
    return sum;
}
void main(){
    
    int n,sum=0;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int j=1;j<=n;j++)
        sum += f(j);
    printf("Sum of the series=%d\n",sum);
}
