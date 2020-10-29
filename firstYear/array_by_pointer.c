#include<stdio.h>
#include<stdlib.h>
int main(){
    int *number,n,sum=0;
    printf("How many numbers will be entered?");
    scanf("%d",&n);
    number = malloc(n*sizeof(int));
    for(int i=0;i<n; i+=1){
        printf("Enter number %d = ",i+1);
        scanf("%d",number+i);
    }
    printf("Entered numbers are :");
    for(int  i=0; i<n;i++){
        printf(" %d ",*(number+i));
        sum += *(number+i);
    }
    printf("\nSum of all entered number is =%d\n",sum);
    return 0;
}
