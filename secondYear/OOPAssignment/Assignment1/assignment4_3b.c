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

void getSize(int* row, int* col){
    printf("Enter the array size space separated integer(row*col): ");
    scanf("%d %d", row, col);
}

void allocate(int*** arr, int row, int col){
    *arr = (int**)malloc(row * sizeof(int*));
    if (*arr){
        FOR(i, row){
            (*arr)[i] = (int*)malloc(sizeof(int) * col);
            if (!(*arr)[i]) MEM_ERROR
        }
    }
    else MEM_ERROR
}

void getInput(int**arr,int row,int col){
    printf("Enter all elements row wise:\n");
    FOR(i, row){
        FOR(j, col){
            scanf("%d", *(arr + i) + j);
        }
    }
}

void print(int**arr,int row,int col){
    printf("Entered array:\n");
    FOR(i, row){
        FOR(j, col){
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

int main(){
    int** arr, row, col;

    //Array size
    getSize(&row, &col);

    //Allocate memory for array
    allocate(&arr,row,col);

    //Initialise array with user input
    getInput(arr,row,col);

    //print the array as a 2d matrix
    print(arr,row,col);

    return 0;

}

