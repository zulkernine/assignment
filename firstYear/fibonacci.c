#include<stdio.h>
void main()
{   
    int n,p_value=0,c_value=1,new_value;
    printf("How many elements of fibonacci series to be printed?\n");
    scanf("%d",&n);    
    printf("%d\t%d\t",p_value,c_value);
    for(int i=0;i<(n-2);i++){   
        new_value = p_value + c_value;
        printf("%d\t",new_value);
        p_value = c_value;
        c_value = new_value;
    }
    printf("\n");
}
