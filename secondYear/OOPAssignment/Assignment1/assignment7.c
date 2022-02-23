/*
    Maintain a list to store roll, name and score of students.
    As and when required student record may be added or deleted.
    Also, the list has to be displayed. Design suitable functions for different operations.
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
    int roll;
    char name[BUF_SIZE];
    int score; // Average score
}student;

typedef struct _Node{
    student data;
    struct _Node* next;
}Node;

typedef struct{
    Node* head;
    Node* tail;
}list;

Node* getNewData(){
    Node* _Node = (Node*)malloc(sizeof(Node));
    if(! _Node) MEM_ERROR

    printf("\nRoll: "); scanf("%d", &(_Node->data.roll));
    char ch;
    while((ch = getchar())!='\n' && ch!=EOF);
    printf("Name: "); scanf("%[^\n]s", _Node->data.name);
    printf("Average score: "); scanf("%d", &(_Node->data.score));

    return _Node;
}

int getOption(){
    printf(
        "\nSelect option:\n"
        "1.Add record\n"
        "2.Delete record\n"
        "3.View all record\n"
        "---Enter 0 to quite---\n"
        "Your Option:- "
    );

    int op;
    scanf("%d", &op);
    getchar();
    return op;
}

void addRecord(list* l){
    printf("Add data:-\n");
    Node* node = getNewData();

    if (l->head){
        l->tail->next = node;
        l->tail = node;
    }
    else{
        l->head = node;
        l->tail = node;
    }

    printf("Record added succesfully :)\n\n");
}

void deleteRecord(list *l){
    int roll;
    printf("\n\n---Deleting a record---\n\nEnter the student Roll number: "); scanf("%d",&roll);

    Node* cur = l->head;
    if(cur->data.roll == roll){
        l->head = cur->next;
        if(!l->head) l->tail = NULL;
    }else{
        Node* prev = NULL;
        while(cur){
            if(cur->data.roll == roll){
                prev->next = cur->next;
                break;
            }else{
                prev = cur;
                cur = cur->next;
            }
        }

        if(l->tail == cur) l->tail = prev;
    }

    if(cur){
        free(cur);
        printf("Record of roll:%d is succesfully deleted :-|\n",roll);
    }else{
        printf("No record found for roll-%d :-(\n",roll);
    }
}

void view(list*l){
    Node* cur = l->head;

    printf("\n\nAll the records are following:-\n\n");
    while(cur){
        printf(
            "Roll:- %d  Score:- %d\n"
            "Name:- %s\n",
            cur->data.roll,
            cur->data.score,
            cur->data.name
        );

        cur = cur->next;
        printf("\n\n");
    }
}

int main(){
    list _list;
    int option;
    
    do{
        option = getOption();
        switch(option){
            case 0:
                printf("Exiting the program :-)\n\n");
                exit(0);
                break;
            case 1:
                addRecord(& _list);
                break;
            case 2:
                deleteRecord(& _list);
                break;
            case 3:
                view(& _list);
                break;
            default:
                printf("Please enter a valid option between 0-3 (both incluseve)\n\n");
        }
    }while(option);

    return 0;
}
