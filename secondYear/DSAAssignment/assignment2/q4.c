#include "set.h"
#include<stdio.h>

void print_set(SET* set){
    printf("SET:");
    for(int i=0;i<set->size;i++) printf("  %d",set->arr[i]);
    printf("\n\n");
}


int main(){
    SET* set1,*set2;
    int size1,size2;
    printf("Capacity of set-1 : ");scanf("%d",&size1);
    printf("Capacity of set-2 : ");scanf("%d",&size2);

    set1 = create_set(size1);
    set2 = create_set(size2);

    while(1){
        printf(
            "Option:-\n"
            "1.Insert into set-1\n"
            "2.Insert into set-2\n"
            "3.Delete from set-1\n"
            "4.Delete from set-2\n"
            "5.Union of set1 and set2\n"
            "6.Intersection of set1 and set2\n"
            "7.exit\n"
            "8.search in set-1\n"
            "Option:- "
        );
        int opt;
        scanf("%d",&opt);

        switch(opt){
            case 1:{
                printf("Enter the number: ");
                int num;scanf("%d",&num);
                insert_key(num,set1);
                printf("New set-1 ");
                print_set(set1);
            }
            break;

            case 2:{
                printf("Enter the number: ");
                int num;scanf("%d", &num);
                insert_key(num, set2);
                printf("New set-2 ");
                print_set(set2);
            }
            break;

            case 3:{
                printf("Enter the number: ");
                int num;scanf("%d", &num);
                delete_key(num, set1);
                printf("New set-1 ");
                print_set(set1);
            }
            break;

            case 4:{
                printf("Enter the number: ");
                int num;scanf("%d", &num);
                delete_key(num, set2);
                printf("New set-2 ");
                print_set(set2);
            }
            break;

            case 5:{
                printf("Union of the sets: ");
                printf("set1 ");print_set(set1);
                printf("set2 ");print_set(set2);

                SET* u = union_set(set1,set2);
                printf("New union set ");
                print_set(u);
                delete_set(u);
            }
            break;

            case 6:{
                printf("Intersection of the sets: ");
                printf("set1 ");print_set(set1);
                printf("set2 ");print_set(set2);

                SET* i = intersection_set(set1, set2);
                printf("New intersection set ");
                print_set(i);
                delete_set(i);
            }
            break;

            case 7:{
                delete_set(set1);
                delete_set(set2);
                exit(0);
            }
            break;

            case 8:{
                printf("Enter number: ");
                int num;scanf("%d",&num);
                num = search_key(num,set1);
                printf(num?"Found\n":"Not FOund\n");
            }
            break;
            

            default: printf("Pease enter a valid number between 1 and 7 inclusive\n\n");
        }
    }
}
