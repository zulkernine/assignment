#include<stdio.h>
int main(){
    int class,sub_failed;
    printf("Enter the obtained class(1/2/3)=");
    scanf("%d",&class);
    printf("Enter the number of subject failed=");
    scanf("%d",&sub_failed);
    switch(class){
        case 1: {
            if(sub_failed<=3)
                printf("Grace marks is = %d\n",sub_failed*5);
            else
                printf("No grace mark\n");
            };break;
        case 2:{
            if(sub_failed<=2)
                printf("Grace marks is =%d\n",sub_failed*4);
            else
                printf("No grace mark\n");
            };break;
        case 3:{
              if(sub_failed<=1)
                printf("Grace marks is =%d\n",sub_failed*5);
              else
                printf("No grace mark\n");
            };break;
    }
    return 0;
}          
