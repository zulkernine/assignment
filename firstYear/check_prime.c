#include<stdio.h>
void main()
{
    int n,c=0;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=1;i<n&&(c!=2);i++)
    {
        if(n%i==0)
        {
            c+=1;      
        }       
    }
    if(c<2){
        printf("%d is a prime number.\n",n);
    }else{
        printf("%d is not a prime number.\n",n);

    }
}
