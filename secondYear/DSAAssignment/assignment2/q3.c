#include<stdio.h>
#include "list.h"
#define _size 15

void print_ns(list_ns* list){
    printf("List(No sentinal): ");
    for (int i = 0;i < list->lastEmptyIndex;i++) printf("  %d", list->arr[i]);
    printf("\n");
}
void print_s(list_s* list){
    printf("List(sentinal): ");
    for (int i = 0; list->arr[i] != SENTINAL && i < (list->size);i++){
        printf("  %d", list->arr[i]);
    }
    printf("\n");
}


int main(){
    list_ns* lns = creat_list_ns(_size);
    list_s* ls = creat_list_s(_size);
    for (int i = 0;i < _size;i++){
        insert_ns(i * 2, lns);
        insert_s(i, ls);
    }

    print_ns(lns);
    print_s(ls);

    //Delete few element
    delete_ns(0, lns);
    delete_s(0, ls);
    for (int i = 8;i < 11;i++){
        delete_ns(i * 2, lns);
        delete_s(i, ls);
    }
    printf("List after deleting few element:\n");
    print_ns(lns);
    print_s(ls);

    //search few element
    for (int i = 6;i < 10;i++){
        //for lns
        int* data = search_ns(i * 2, lns);
        if (data) printf("Found %d in lns\n", *data);
        else printf("Didn't find %d in lns\n", i);

        data = search_s(i, ls);
        if (data) printf("Found %d in ls\n", *data);
        else printf("Didn't find %d in ls\n", i);
    }

    printf("_size of lns:%d\n", size_ns(lns));
    printf("_size of ls:%d\n", size_s(ls));

    delete_list_ns(lns);
    delete_list_s(ls);

    return 0;
}
