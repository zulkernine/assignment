#include<stdio.h>
void main()
{
    int n,sum=0;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        sum += i*(i+1);
    }
    printf("Sum of the series=%d\n",sum);
        
    
}
