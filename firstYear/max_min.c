#include<stdio.h>
void main()
{
    int max,min;
    int x,y,z;
    printf (" Enter 3 number=");
    scanf("%d%d%d",&x,&y,&z);
    max=min=x;
    if(max<y){
        max=y;
    }
    if(max<z){
        max=z;
    }
    if(min>y){
        min=y;
    }
    if(min>z){
        min=z;
    }
    printf("max = %d \nmin=%d\n",max,min);
}
