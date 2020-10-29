// Implement a one dimensional array of integers where array size of the array will be 
// provided during runtime.Accept the value for the elementsand print those using pointers.

#include<stdio.h>
#include<stdlib.h>

int main(){
    int* arr,size;

    //get size input
    printf("Size of the array: ");
    scanf("%d",&size);

    //Allocate memory
    arr = (int*)malloc(size * sizeof(int));
    if(!arr){
        printf("Failed to allocate memory for the array :(\n");
        exit(1);
    }
    
    //Input elements of the array
    printf("Enter all elements space/new-line separated: ");
    for(int i=0;i<size;i++)
        scanf("%d",arr+i);
    
    //Output the elemnts
    printf("All the array elements are: ");
    for(int i=0;i<size;i++) printf("%d ",arr[i]);
    printf("\n");

    return 0;
}
