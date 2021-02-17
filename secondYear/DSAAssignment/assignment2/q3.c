#include<stdio.h>
#include "list.h"
#define size 15

void print_ns(list_ns* list){
    printf("List(No sentinal): ");
    for(int i=0;i<list->lastEmptyIndex;i++) printf("  %d",list->arr[i]);
    printf("\n");
}
void print_s(list_s* list){
    printf("List(No sentinal): ");
    for (int i = 0; list->arr[i]!=SENTINAL;i++) printf("  %d", list->arr[i]);
    printf("\n");
}


int main(){
    list_ns* lns = creat_list_ns(size);
    list_s* ls = creat_list_s(size);
    for(int i=0;i<size;i++){
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
    for(int i=6;i<10;i++){
        //for lns
        int* data = search_ns(i*2,lns);
        if(data) printf("Found %d in lns\n",*data);
        else printf("Didn't find %d in lns\n",i);

        data = search_s(i, ls);
        if (data) printf("Found %d in ls\n", *data);
        else printf("Didn't find %d in ls\n", i);
    }

    printf("Size of lns:%d\n", size_ns(lns));
    printf("Size of ls:%d\n", size_s(ls));

    return 0;
}
