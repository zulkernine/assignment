/*
    Write programs for linear search and binary search for searching integers,
    floating point numbers and words in arrays of respective types.
*/

//Floating number search

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int linearSearchInt(char** arr, int size, char* str){
    for (int i = 0;i < size;i++){
        if (! strcmp(arr[i],str))
            return i;
    }

    return -1;
}

int binarySearchInt(char** arr, int start, int end, char* str){
    int middle = (start + end) / 2;
    char* curNum = arr[middle];

    if (arr[end] < arr[start]){
        printf("Array not sorted, binary search is not applicable\n\n");
        return -1;
    }

    int bool = strcmp(curNum,str);
    if (bool == 0) return middle;
    else{
        if (start == end) return -1;
        else {
            if (bool<0) {
                return binarySearchInt(arr, middle + 1, end, str);
            }
            else {
                return binarySearchInt(arr, start, middle, str);
            }
        }
    }
}

int main(){
    int size;char temp[100];
    printf("Enter array size: ");
    scanf("%d", &size);

    char** arr;
    arr = (char**)malloc(size * sizeof(char*));

    printf("Enter all string in a new line:-\n");
    for (int i = 0;i < size;i++){
        while((getchar()!='\n'));
        scanf("%[^\n]s", temp);
        arr[i] = (char*)malloc(sizeof(char)*(strlen(temp) + 2));
        strcpy(arr[i],temp);
    }

    int index;
    printf("Enter the string to search index: ");
    while ((getchar() != '\n')); scanf("%[^\n]s", temp);

    index = linearSearchInt(arr, size, temp);
    printf("Linear search index: %d\n\n", index);
    index = binarySearchInt(arr, 0, size - 1, temp);
    printf("Binary search index: %d\n\n", index);

    //free memory
    for(int i=0;i<size;i++) free(arr[i]);
    free(arr);

    return 0;
}

