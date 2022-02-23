#include<stdio.h>
void main(){
    int n,sum=0;
    printf("Enter a number=");
    scanf("%d",&n);
    while (n>0)
    {
        sum+=n%10;
        n=n/10;
        /* code */
    }
    printf("\nsum=%d\n",sum);    
}
