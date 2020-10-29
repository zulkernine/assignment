/*
    Implement Q.5 using structure :-
      5.Store name and age of number of persons (number provided at run time).
        Collect the data and display data in the ascending order of age.
        Implement without using structure. Write functions for memory allocation of the list,
        sorting and display of data.
*/

#include<stdio.h>
#include<stdlib.h>

#define BUF_SIZE 25
#define FOR(i,size) for(int i=0;i< size;i++)
#define FOR1(i,size) for(int i=1;i<=size;i++)
#define MEM_ERROR {\
    printf("Can't allocate sufficient memory :(\n");\
    exit(1);\
}

typedef struct{
    int age;
    char name[BUF_SIZE];
}person;

void allocate(int size, person** arr){
    *arr = (person*)malloc(sizeof(person) * size);

    if (!(*arr)) MEM_ERROR
}

void getInput(int size, person* arr){
    FOR(i, size){
        printf("Age of person %d: ", i + 1);
        scanf("%d", &(arr[i].age));
        getchar();
        printf("Name of person %d: ", i + 1);
        scanf("%[^\n]s", arr[i].name);
    }
}

void sort(int size, person* arr){
    FOR(i, size){
        for (int j = i;j < size;j++){
            if (arr[i].age > arr[j].age){
                //swap person data
                person temp;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void print(int size, person* arr){
    FOR(i, size){
        printf("\n%d. Age:%d  Name:%s\n", i + 1, arr[i].age, arr[i].name);
    }
}

int main(){
    int num;
    person* arr;

    //Get dimension of list
    printf("Length of the list: ");
    scanf("%d", &num);

    //Allocate memory
    allocate(num, &arr);

    //Initialise the list
    getInput(num, arr);

    //Sort the list
    sort(num, arr);

    //Print the list
    print(num, arr);

    return 0;
}
