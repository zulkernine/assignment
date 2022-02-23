/*
    Define an ADT for List.Write C data structure representation and functions for the operations on the Listin a
    Header file with array as the base data structure.Write a menu-driven main program in a separate file for
    testing the different operations and include the above header file.Two data structures with and without using
    sentinels in arrays are to be implemented.
*/
#include<stdlib.h>
#define SENTINAL -2147483648

//No sentinal: _ns
typedef struct list_ns{
    int* arr;
    int size;
    int lastEmptyIndex;
}list_ns;

//Using sentinal: _s
typedef struct list_s{
    int* arr;
    int size;
}list_s;

//Return ponter to the created list else null
list_ns* creat_list_ns(int size);
list_s* creat_list_s(int size);

//Returns index after inserting element, if fails, returns -1
int insert_ns(int data, list_ns* list);
int insert_s(int data, list_s* list);

//Search elements for key k, returns pointer to that data
int* search_ns(int k, list_ns* list);
int* search_s(int k, list_s* list);

//Delete data with key k,internal elements will be altered to remove free space
void delete_ns(int k, list_ns* list);
void delete_s(int k, list_s* list);

int size_ns(list_ns* list);
int size_s(list_s* list);

int is_empty_ns(list_ns* list);
int is_empty_s(list_s* list);

int is_full_ns(list_ns* list);
int is_full_s(list_s* list);

void delete_list_ns(list_ns* list);
void delete_list_s(list_s* list);
/* Implementation */


//Return ponter to the created list else null
list_ns* creat_list_ns(int size){
    list_ns* ptr = (list_ns*)malloc(sizeof(list_ns));
    ptr->size = size;
    ptr->arr = (int*)malloc(sizeof(int) * size);
    ptr->lastEmptyIndex = 0;

    return ptr;
}
list_s* creat_list_s(int size){
    list_s* ptr = (list_s*)malloc(sizeof(list_s));
    ptr->size = size;
    ptr->arr = (int*)malloc(sizeof(int) * (size+1));
    for (int i = 0;i < size+1;i++) ptr->arr[i] = SENTINAL;

    return ptr;
}

//Returns index after inserting element, if fails, returns -1
int insert_ns(int data, list_ns* list){
    if (list->lastEmptyIndex < list->size){
        list->arr[list->lastEmptyIndex] = data;
        list->lastEmptyIndex++;
        return (list->lastEmptyIndex - 1);
    }
    else{
        return -1;
    }
}
int insert_s(int data, list_s* list){
    for (int i = 0;i < list->size;i++){
        if (list->arr[i] == SENTINAL){
            list->arr[i] = data;
            return i;
        }
    }

    return -1;
}

//Search elements for key k, returns pointer to that data
int* search_ns(int k, list_ns* list){
    for (int i = 0;i < list->lastEmptyIndex;i++){
        if (list->arr[i] == k) return (list->arr + i);
    }
    return NULL;
}
int* search_s(int k, list_s* list){
    for (int i = 0;list->arr[i] != SENTINAL || i<list->size;i++){
        if (list->arr[i] == k) return (list->arr + i);
    }
    return NULL;
}

//Delete data with key k,internal elements will be altered to remove free space
void delete_ns(int k, list_ns* list){
    int index = search_ns(k,list) - list->arr;
    for(int i=index;(i+1)<(list->lastEmptyIndex);i++){
        list->arr[i] = list->arr[i+1];
    }
    list->lastEmptyIndex--;
}
void delete_s(int k, list_s* list){
    int index = search_s(k, list) - list->arr;
    for (int i = index;list->arr[i]!=SENTINAL;i++){
        list->arr[i] = list->arr[i + 1];
    }
}

int size_ns(list_ns* list){
    return list->lastEmptyIndex;
}
int size_s(list_s* list){
    for(int i=0;i<list->size;i++){
        if (list->arr[i]==SENTINAL) return i;
    }
    return list->size;
}


int is_empty_ns(list_ns* list){
    if (list->lastEmptyIndex == 0) return 1;
    else return 0;
}
int is_empty_s(list_s* list){
    return (list->arr[0] == SENTINAL);
}

int is_full_ns(list_ns* list){
    if(list->lastEmptyIndex == list->size) return 1;
    else return 0;
}
int is_full_s(list_s* list){
    return (list->arr[list->size-1] == SENTINAL);
}

void delete_list_ns(list_ns* list){
    if(list){
        if(list->arr) free(list->arr);
        free(list);
    }
}
void delete_list_s(list_s* list){
    if (list){
        if (list->arr) free(list->arr);
        free(list);
    }
}
