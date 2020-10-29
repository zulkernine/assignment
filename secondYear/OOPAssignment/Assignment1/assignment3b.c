// Implement a two dimensional array of integers using 
// a) pointer to an array and 
// b) array of pointers.
// Accept the value for the elementsand print those.

#include<stdio.h>
#include<stdlib.h>

#define FOR(i,size) for(int i=0;i< size;i++)
#define FOR1(i,size) for(int i=1;i<=size;i++)
#define MEM_ERROR {\
    printf("Can't allocate sufficient memory :(\n");\
    exit(1);\
}

int main(){
    int **arr,row,col;

    //Array size
    printf("Enter the array size space separated integer(row*col): ");
    scanf("%d %d",&row,&col);

    //Allocate memory for array
    arr = (int**)malloc(row*sizeof(int*));
    if(arr){
        FOR(i,row){
            arr[i] = (int*)malloc(sizeof(int)*col);
            if(!arr[i]) MEM_ERROR
        }
    }else MEM_ERROR

    //Initialise array with user input
    printf("Enter all elements row wise:\n");
    FOR(i,row){
        FOR(j,col){
            scanf("%d",*(arr+i)+j);
        }
    }

    //print the array as a 2d matrix
    printf("Entered array:\n");
    FOR(i,row){
        FOR(j,col){
            printf("%d ",*(*(arr+i)+j));
        }
        printf("\n");
    }

    return 0;

}
