#include<stdio.h>
#include<stdlib.h>

int comparisonOrder(int n1, int n2){
    if (n1<=n2) return -1; //ascending order
    else return 1; //Descending order
}


int main(){
    int *arr,size;
    printf("Array size: ");
    scanf("%d",&size);
    if(size < 0){
        printf("Invalid size :(\n");
        return 1;
    }

    arr = (int*) malloc(size*sizeof(int));

    printf("Enter all element of array: ");
    for(int i=0;i<size;i++){
        scanf("%d",arr+i);
    }

    if(size<2){
        printf("Array is sorted but order can't be determind.\n");
    }

    int order = comparisonOrder(arr[0],arr[1]);
    for(int i=1;i<size-1;i++){
        if(order == comparisonOrder(arr[i],arr[i+1])) continue;
        else{
            printf("Array is not sorted\n");
            return 0;
        }
    }

    if(order == -1){
        printf("Array is sorted in ascending order. \n");
    }else if(order == 1){
        printf("Array is sorted in descending order.\n");
    }

    return 0;
}