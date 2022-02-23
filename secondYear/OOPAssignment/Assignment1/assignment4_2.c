// Implement the programs in Q.2 and 3 breaking it into functions for 
// i) getting the dimensions from user, 
// ii) dynamic memory allocation, 
// iii) accepting the valuesand 
// iv) printing the values.


#include<stdio.h>
#include<stdlib.h>

#define FOR(i,size) for(int i=0;i< size;i++)
#define FOR1(i,size) for(int i=1;i<=size;i++)
#define MEM_ERROR {\
    printf("Can't allocate sufficient memory :(\n");\
    exit(1);\
}

int getSize(){
    int size;
    printf("Size of the array: ");
    scanf("%d", &size);
    return size;
}

void allocate(int**arr,int size){
    *arr = (int*)malloc(size * sizeof(int));
    if (!(*arr)){
        printf("Failed to allocate memory for the array :(\n");
        exit(1);
    }
}

void getElements(int *arr,int size){
    printf("Enter all elements space/new-line separated: ");
    FOR(i,size) scanf("%d", arr + i);
}

void print(int *arr,int size){
    printf("All the array elements are: ");
    FOR(i,size) printf("%d ", arr[i]);
    printf("\n");
}

int main(){
    int* arr, size;

    //get size input
    size = getSize();

    //Allocate memory
    allocate(&arr,size);

    //Input elements of the array
    getElements(arr,size);

    //Output the elemnts
    print(arr,size);
    return 0;
}
