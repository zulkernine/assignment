#include<stdio.h>
void main(){
    int n;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=1;i<=100;i++){
        if(i%n==0)
            printf("%d\t",i);
    }  
    printf("\n");          
}
