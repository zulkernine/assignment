// Implement a two dimensional array of integers using 
// a) pointer to an array and 
// b) array of pointers.
// Accept the value for the elementsand print those.

#include<stdio.h>
#include<stdlib.h>

int main(){
    int *ptr,col,row;

    //get 2d array size
    printf("Please input array size space separated(r*c): ");
    scanf("%d %d",&row,&col);

    //Allocate memory
    ptr = (int*)malloc(row*col*sizeof(int));
    if(!ptr){
        printf("Can't allocate memory :(\n");
        exit(1);
    }

    //Take the input:
    printf("Enter all the array elemnt row by row:\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",ptr + i*col+j);
        }
    }

    //Output all the lement as a 2d matrix
    printf("Entered array is:\n");
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            printf("%d ",ptr[r*col + c]);
        }
        printf("\n");
    }

    return 0;
}
