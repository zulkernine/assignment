/*
    Define an ADT for Set.Write C data representation and functions for the operations on the Set in a Header file,
    with array as the base data structure.Write a menu-driven main program in a separate file for testing the
    different operations and include the above header file.

    Operation:-
    1.Insert
    2.Delete
    3.Search
    4.Union
    5.Intersection
*/
#include<stdlib.h>

/* Numbers are stored in a sorted order */
typedef struct{
    int* arr;
    int size;
    int capacity;
}SET;

//Insert a key
void insert_key(int key, SET* set);
//Deete a key
void delete_key(int key, SET* set);
//Search: return boolean if key exist or not
int search_key(int key, SET* set);
//Union of two set
SET* union_set(SET* set1, SET* set2);
//Intersection of two set
SET* intersection_set(SET* set1, SET* set2);
//Delete a set
void delete_set(SET* set);
//Create a set
SET* create_set(int capacity);
//Size of set or Number of elements in set
int size_of_set(SET* set);


/* Implementation */


//Delete a set
void delete_set(SET* set){
    if (set){
        if (set->arr) free(set->arr);
        free(set);
    }
}

//Create a set
SET* create_set(int capacity){
    SET* set = (SET*)malloc(sizeof(SET));
    set->capacity = capacity;
    set->size = 0;
    set->arr = (int*)malloc(sizeof(int) * capacity);

    return set;
}

//Insert a key
// void insert_key(int key, SET* set){
//     if (!search_key(key, set) && set->size != set->capacity){
//         if (set->size == 0) set->arr[set->size++] = key;
//         else{
//             for (int i = set->size;i > 0;i--){
//                 if (key < set->arr[i - 1]){
//                     set->arr[i] = set->arr[i - 1];
//                 }
//                 else{
//                     set->arr[i] = key;
//                 }
//             }

//             set->size++;
//         }

//     }
// }

//Deete a key
void delete_key(int key, SET* set){
    int index_of_key;
    for (index_of_key = 0;index_of_key < set->size;index_of_key++)
        if (set->arr[index_of_key] == key) break;

    if (index_of_key != set->size){
        for (int i = index_of_key;i < set->size;i++){
            set->arr[i] = set->arr[i + 1];
        }

        set->size--;
    }

}

//Search: return boolean if key exist or not
int search_key(int key, SET* set){
    int start, middle, end;

    start = 0; end = set->size - 1;
    while (start < end){
        middle = (start + end) / 2;
        if (set->arr[middle] == key) return 1;
        else if (set->arr[middle] > key){
            end = middle - 1;
        }
        else{
            start = middle + 1;
        }
    }

    return 0;
}

//Union of two set
SET* union_set(SET* set1, SET* set2){
    int capacity = (set1->size + set2->size + set1->capacity + set2->capacity) / 4;
    SET* set = create_set(capacity);

    int i = 0, j = 0, k = 0;
    while (i < set1->size && j < set2->size){
        if (set1->arr[i] < set2->arr[j]) set->arr[k++] = set->arr[i++];
        else if (set1->arr[i] > set2->arr[j]) set->arr[k++] = set2->arr[j++];
        else {
            set->arr[k++] = set1->arr[i++];
            j++;
        }
    }
    while (i < set1->size) set->arr[k++] = set->arr[i++];
    while (j < set2->size) set->arr[k++] = set2->arr[j++];
    set->size = k;

    return set;
}

//Intersection of two set
SET* intersection_set(SET* set1, SET* set2){
    int capacity = (set1->size + set2->size + set1->capacity + set2->capacity) / 4;
    SET* set = create_set(capacity);

    int i = 0, j = 0, k = 0;
    while (i < set1->size && j < set2->size){
        if (set1->arr[i] < set2->arr[j]) i++;
        else if (set1->arr[i] > set2->arr[j]) j++;
        else {
            set->arr[k++] = set1->arr[i++];
            j++;
        }
    }
    set->size = k;

    return set;
}

//Size of set or Number of elements in set
int size_of_set(SET* set){
    return set->size;
}

