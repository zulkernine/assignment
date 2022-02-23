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

void getSize(int*row,int*col){
    printf("Please input array size space separated(r*c): ");
    scanf("%d %d", row, col);
}

void allocateMemory(int**ptr,int size){
    *ptr = (int*)malloc( size * sizeof(int));
    if (!(*ptr)) MEM_ERROR
}

void getInput(int *ptr,int row,int col){
    printf("Enter all the array elemnt row by row:\n");
    FOR(i,row){
        FOR(j,col){
            scanf("%d", ptr + i * col + j);
        }
    }
}

void print(int* ptr, int row, int col){
    printf("Entered array is:\n");
    FOR(r,row){
        FOR(c,col){
            printf("%d ", ptr[r * col + c]);
        }
        printf("\n");
    }
}

int main(){
    int* ptr, col, row;

    //get 2d array size
    getSize(&row,&col);

    //Allocate memory
    allocateMemory(&ptr,row*col);

    //Take the input:
    getInput(ptr,row,col);

    //Output all the lement as a 2d matrix
    print(ptr,row,col);

    return 0;
}
