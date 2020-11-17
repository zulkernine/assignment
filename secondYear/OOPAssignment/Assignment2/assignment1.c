/*
    Write a program to store student information in a file and to do the following operations.
    Information includes roll, name, and score in five subjects.
    User may like to add record (ensure roll number is unique), display all records showing roll, name and total score.
    User may search for the record against a roll. User may edit the details a record.User may delete record.
    Deletion may be logical (by some means indicate it is an invalid record and to be avoided in processing) and 
    physical (file will not have the record).
*/

#include<stdio.h>
#include<stdlib.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define FLUSH_CIN while(getchar()!='\n')

char DATA_FILE_NAME[30];

typedef struct{
    int roll;
    char name[20];
    int score[5];
}StudentData;

int SIZE=100;

int getOption(){
    printf(
        "\n\n---------------------------\n\n"
        "Choose an option:\n"
        "1.Add data\n"
        "2.Delete data\n"
        "3.Edit a data\n"
        "4.View all student data\n"
        "--Enter 0 to quit--\n\n"
        "Option:- "
    );
    int n;scanf("%d",&n);
    return n;
}

void InitFromLocalFile(StudentData** ptr,char* fileName){
    FILE *input;
    if ((input = fopen(fileName, "rb")) == NULL){
        printf("Can't find previously saved data :)\n");

        //Init default values
        *ptr = (StudentData*)malloc(SIZE * sizeof(StudentData));
        FOR(i, SIZE){
            (*ptr)[i].roll = -1;
        }
    }else{
        fread(&SIZE, sizeof(int), 1, input);
        *ptr = (StudentData*)malloc(SIZE * sizeof(StudentData));
        fread(*ptr,sizeof(StudentData),SIZE,input);
        fclose(input);
        printf("Saved data loaded in the memory :)\n\n\n");
    }
}

void saveDataTOLOcalFile(StudentData* ptr, char* fileName){
    FILE* output;
    if ((output = fopen(fileName, "wb")) == NULL){
        printf("Can't save data to memory :(\n\n");
    }else{
        fwrite(&SIZE,sizeof(int),1,output);
        fwrite(ptr,sizeof(StudentData),SIZE,output);
        printf("Data saved on local file succesfully :-o\n\n");
    }

}

void expandArr(StudentData** arr,int newSize){
    int tempSize = newSize + 5;

    StudentData* tempArr = (StudentData*)realloc(*arr,sizeof(StudentData) * tempSize);

    if(!tempArr){
        printf("Failed to allocate memory :( \n\n");
    }else{
        *arr = tempArr;
        for(int i=SIZE;i<tempSize;i++)
            (*arr)[i].roll = -1;

        SIZE = tempSize;
    }
}

int getRoll(){
    int roll;
    printf("\n\n---Add new Record---\n");
    printf("Roll: ");scanf("%d", &roll);
    return roll;
}

void addRecord(StudentData**ptr){
    int roll = getRoll();

    if(roll>=SIZE){
        expandArr(ptr,roll);
    }

    if((*ptr)[roll].roll != -1){
        printf("Students record already exist for roll no. %d . Cann't enter new record.\n\n",roll);
    }else{
        (*ptr)[roll].roll = roll;
        printf("Full name: "); FLUSH_CIN;
        scanf("%[^\n]s",(*ptr)[roll].name);
        printf("Score in 5 subjects(Beng Eng Math Sci His): ");
        FOR(i,5){
            scanf("%d",(*ptr)[roll].score + i);
        }
        printf("\n1 Record added :)\n\n");
    }
}

void deleteRecord(StudentData*arr){
    int roll = getRoll();

    if(roll>=SIZE){
        printf("No record exist for roll %d\n",roll);
    }else if(arr[roll].roll == -1){
        printf("No record for roll %d exist or already has been deleted\n",roll);
    }else{
        arr[roll].roll = -1;
        printf("Record of roll %d is deleted succesfully\n\n",roll);
    }
}

void editRecord(StudentData*arr){
    int roll = getRoll();

    if (roll >= SIZE || arr[roll].roll == -1){
        printf("No record exist for this roll number.\n\n");
        return;
    }else{
        char ch;

        //Edit name
        FLUSH_CIN;
        printf("Edit name?(y for yes): ");
        scanf("%c",&ch);
        if(ch=='y'){
            printf("New Name: ");
            FLUSH_CIN;
            scanf("%[^\n]s",arr[roll].name);
        }

        //Marks
        int i;
        while(1){
            printf(
                "Select the subject number to change marks:\n"
                "1.Beng  2.Eng  3.Math  4.Sci  5.His\n"
                "Enter 0 to exit\n"
                "code:- "
            );
            scanf("%d",&i);
            if(i>=5 || i<0){
                printf("Code must be between 0 and 5\n\n");
            }else if(i==0){
                break;
            }else{
                printf("New score: ");
                scanf("%d",arr[roll].score + i -1);
            }
        }

    }
}

void viewList(StudentData*arr){
    printf("\n\n---All students List---\n\n");
    FOR(i,SIZE){
        if(arr[i].roll != -1) printf(
            "\n%d\nRoll:%d\n"
            "Name: %s\n"
            "Beng:%d  Eng:%d  Math:%d  Sci:%d  His:%d\n\n",i,
            arr[i].roll, arr[i].name, arr[i].score[0], arr[i].score[1],
            arr[i].score[2], arr[i].score[3], arr[i].score[4]
        );
    }
}

int main(){
    StudentData* arr;

    printf("Enter File name(IF not exist, it will be created during saving): ");
    scanf("%s",DATA_FILE_NAME);

    InitFromLocalFile(&arr,DATA_FILE_NAME);

    while(1){
        int option = getOption();
        switch(option){
            case 0:
                saveDataTOLOcalFile(arr, DATA_FILE_NAME);
                printf("Exiting the program\n");
                exit(0);
            case 1:
                addRecord(&arr);
                break;
            case 2:
                deleteRecord(arr);
                break;
            case 3:
                editRecord(arr);
                break;
            case 4:
                viewList(arr);
                break;
            default:
                printf("Option must be between 0 and 4\n\n");
        }
    }
}


