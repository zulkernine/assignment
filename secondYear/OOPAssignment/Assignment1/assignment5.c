/*
    Store name and age of number of persons (number provided at run time). 
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

void allocate(int size,int**ages,char***names){
    *ages = (int*)malloc(size * sizeof(int));
    if(!(*ages)) MEM_ERROR

    *names = (char**)malloc(size * sizeof(char*));
    if(*(names)){
        FOR(i,size){
            (*names)[i] = (char*)malloc(BUF_SIZE * sizeof(char));
            if(!(*names)[i]) MEM_ERROR
        }
    }else MEM_ERROR
}

void getInput(int size,int*age,char**names){
    FOR(i,size){
        printf("Age of person %d: ",i+1);
        scanf("%d",age+i);
        getchar();
        printf("Name of person %d: ",i+1);
        scanf("%[^\n]s",names[i]);
    }
}

void sort(int size,int*ages,char**names){
    FOR(i,size){
        for(int j=i;j<size;j++){
            if(ages[i] > ages[j]){
                //swap age
                int temp = ages[i];
                ages[i] = ages[j];
                ages[j] = temp;

                //swap names corresponding to indexes
                char* str = names[i];
                names[i] = names[j];
                names[j] = str;
            }
        }
    }
}

void print(int size,int*ages,char**names){
    FOR(i,size){
        printf("\n%d. Age:%d  Name:%s\n",i+1,ages[i],names[i]);
    }
}

int main(){
    int num,*ages;
    char**names;

    //Get dimension of list
    printf("Length of the list: ");
    scanf("%d",&num);

    //Allocate memory
    allocate(num,&ages,&names);

    //Initialise the list
    getInput(num,ages,names);

    //Sort the list
    sort(num,ages,names);

    //Print the list
    print(num,ages,names);

    return 0;
}
