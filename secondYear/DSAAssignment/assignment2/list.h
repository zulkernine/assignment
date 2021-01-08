/*
    Define an ADT for List.Write C data structure representation and functions for the operations on the Listin a 
    Header file with array as the base data structure.Write a menu-driven main program in a separate file for 
    testing the different operations and include the above header file.Two data structures with and without using 
    sentinels in arrays are to be implemented.
*/

//No sentinal
typedef struct list_ns{
    int* arr;
    int size;
    int lastEmptyIndex;
};

//Using sentinal
typedef struct list_s{
    int * arr;
    int size;
};

//Return ponter to the created list else null
list_ns* creat_list_ns(int size);
list_s* creat_list_s(int size);

//Returns index after inserting element, if fails, returns -1
int insert_ns(int data,list_ns* list);
int insert_s(int data, list_s* list);

//Search elements for key k, returns pointer to that data
int* search_ns(int k, list_ns* list);
int* search_s(int k, list_s* list);

//Delete data with key k,internal elements will be altered to remove free space
void delete_ns(int k, list_ns* list);
void delete_s(int k, list_s* list);

int size_ns(list_ns* list);
int size_s(list_s* list);
