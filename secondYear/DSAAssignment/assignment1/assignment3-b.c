/*
    Write programs for linear search and binary search for searching integers,
    floating point numbers and words in arrays of respective types.
*/

//Floating number search

#include<stdio.h>
#include<stdlib.h>

int linearSearchInt(float* arr, int size, float num){
    for (int i = 0;i < size;i++){
        if (arr[i] == num)
            return i;
    }

    return -1;
}

int binarySearchInt(float* arr, int start, int end, float num){
    int middle = (start + end) / 2;
    float curNum = arr[middle];

    if (arr[end] < arr[start]){
        printf("Array not sorted, binary search is not applicable\n\n");
        return -1;
    }

    if (curNum == num) return middle;
    else{
        if (start == end) return -1;
        else {
            if (curNum < num) {
                return binarySearchInt(arr, middle + 1, end, num);
            }
            else {
                return binarySearchInt(arr, start, middle, num);
            }
        }
    }
}

int main(){
    int size;
    printf("Enter array size: ");
    scanf("%d", &size);

    float* arr;
    arr = (float*)malloc(size * sizeof(float));

    printf("Enter all elements space separated: ");
    for (int i = 0;i < size;i++) scanf("%f", arr + i);

    float rnum;int index;
    printf("Enter a number to search index: "); scanf("%f", &rnum);

    index = linearSearchInt(arr, size, rnum);
    printf("Linear search index: %d\n\n", index);
    index = binarySearchInt(arr, 0, size - 1, rnum);
    printf("Binary search index: %d\n\n", index);

    printf("Actual array(i:el):- ");
    for (int i = 0;i < size;i++) printf("%d:%f ", i, arr[i]);
    printf("\n");
    free(arr);
    return 0;
}

