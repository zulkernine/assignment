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

typedef struct{
    int roll;
    int valid;
    char name[20];
    int score[5];
}StudentData;

long long search(char* fn, int roll);


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
    int n;scanf("%d", &n);
    return n;
}


int getRoll(){
    int roll;
    printf("Roll: ");scanf("%d", &roll);
    return roll;
}

void addRecord(char* fn){
    int roll = getRoll();
    StudentData data;

    if (search(fn, roll) != -1){
        printf("Students record already exist for roll no. %d . Cann't enter new record.\n\n", roll);
    }
    else{
        data.roll = roll;
        printf("Full name: "); FLUSH_CIN;
        scanf("%[^\n]s", data.name);
        printf("Score in 5 subjects(Beng Eng Math Sci His): ");
        FOR(i, 5){
            scanf("%d", data.score + i);
        }

        //Save into file
        FILE* output = fopen(fn, "ab");
        if (output == NULL){
            printf("Can't open file, check your user permission. :(\n\n");
            exit(1);
        }
        else{
            fwrite(&data, sizeof(StudentData), 1, output);
            fclose(output);
        }

        printf("\n1 Record added :)\n\n");
    }
}

void deleteRecord(char* fn){
    int roll = getRoll();

    long long pos = search(fn, roll);

    if (pos == -1){
        printf("Record for roll %d doesn't exist or already deleted.\n\n", roll);
    }
    else{
        printf(
            "What deletion you prefer?\n1.Logical Deletion\n2.Physical Deletion\noption:- "
        );
        int option;
        scanf("%d", &option);

        switch (option){
        case 1:
        {
            FILE* fp;
            fp = fopen(fn, "ab");
            if (fp == NULL){
                printf("Can't open file, check your user permission. :(\n\n");
                exit(1);
            }
            else{
                fseek(fp, pos, SEEK_SET);
                StudentData data;
                fread(&data, sizeof(StudentData), 1, fp);
                data.roll = -1;
                fseek(fp, pos, SEEK_SET);
                fwrite(&data, sizeof(StudentData), 1, fp);
                fclose(fp);
            }
        }
        break;

        case 2:
        {
            FILE* fp = fopen(fn, "ab");
            if (fp == NULL){
                printf("Can't open file, check your user permission. :(\n\n");
                exit(1);
            }
            else{
                //Logical delete first
                fseek(fp, pos, SEEK_SET);
                StudentData data;
                fread(&data, sizeof(StudentData), 1, fp);
                data.roll = -1;
                fseek(fp, pos, SEEK_SET);
                fwrite(&data, sizeof(StudentData), 1, fp);

                // Remove all logically deleted data
                rewind(fp);

                char tempName[] = "dgdg5da5dfs4agg.temp";
                FILE *temp = fopen("dgdg5da5dfs4agg.temp","w+b");
                if(temp==NULL){
                    printf("Can't create file \n\n");
                    exit(1);
                }

                while(!feof(fp)){
                    fread(&data, sizeof(StudentData), 1, fp);
                    if (data.roll != -1) fwrite(&data, sizeof(StudentData), 1, temp);
                }

                fclose(fp);
                fclose(temp);

                if (remove(fn)) {
                    printf("Cannot erase file.\n");
                    exit(1);
                }

                char command[100];
                sprintf(command,"mv %s %s",tempName,fn);
                system(command);

            }
        }
        break;

        default:

            break;
        }
    }
}

void editRecord(char* fn){
    int roll = getRoll();

    long long pos = search(fn, roll);

    if (pos == -1){
        printf("No record exist for this roll number.\n\n");
        return;
    }
    else{

        StudentData data;
        FILE* fp = fopen(fn, "ab");
        if (fp == NULL){
            printf("Can't open file!\n");
            exit(1);
        }

        fseek(fp, pos, SEEK_SET);
        fread(&data, sizeof(StudentData), 1, fp);

        char ch;

        //Edit name
        FLUSH_CIN;
        printf("Edit name?(y for yes): ");
        scanf("%c", &ch);
        if (ch == 'y'){
            printf("New Name: ");
            FLUSH_CIN;
            scanf("%[^\n]s", data.name);
        }

        //Marks
        int i;
        while (1){
            printf(
                "Select the subject number to change marks:\n"
                "1.Beng  2.Eng  3.Math  4.Sci  5.His\n"
                "Enter 0 to exit\n"
                "code:- "
            );
            scanf("%d", &i);
            if (i >= 5 || i < 0){
                printf("Code must be between 0 and 5\n\n");
            }
            else if (i == 0){
                break;
            }
            else{
                printf("New score: ");
                scanf("%d", data.score + i - 1);
            }
        }

        //Save
        fseek(fp, pos, SEEK_SET);
        fwrite(&data, sizeof(StudentData), 1, fp);
        fclose(fp);
    }
}

void viewList(char* fn){
    printf("\n\n---All students List---\n\n");

    FILE* fp;
    fp = fopen(fn, "rb");
    if (fp == NULL){
        printf("Can't open file :(\n");
        exit(1);
    }

    StudentData data;   
    while (!feof(fp)){
        fread(&data, sizeof(StudentData), 1, fp);
        if (data.roll != -1){
            printf(
                "\nRoll:%d\n"
                "Name: %s\n"
                "Beng:%d  Eng:%d  Math:%d  Sci:%d  His:%d\n\n",
                data.roll, data.name, data.score[0], data.score[1],
                data.score[2], data.score[3], data.score[4]
            );
        }
    }

    fclose(fp);
}

long long search(char* fn, int roll){
    FILE* fp = fopen(fn,"rb");
    if(fp==NULL){
        return -1;
    }

    StudentData data;

    while(!feof(fp)){
        fread(&data,sizeof(StudentData),1,fp);

        long long pos = ftell(fp);
        if(data.roll == roll) {
            fclose(fp);
            return pos;
        }
    }

    return -1;
}


int main(){
    char DATA_FILE_NAME[30];

    printf("Enter File name(IF not exist, it will be created during saving): ");
    scanf("%s", DATA_FILE_NAME);

    // InitFromLocalFile(&arr, DATA_FILE_NAME);

    while (1){
        int option = getOption();
        switch (option){
        case 0:
            // saveDataTOLOcalFile(arr, DATA_FILE_NAME);
            printf("Exiting the program\n");
            exit(0);
        case 1:
            addRecord(DATA_FILE_NAME);
            break;
        case 2:
            deleteRecord(DATA_FILE_NAME);
            break;
        case 3:
            editRecord(DATA_FILE_NAME);
            break;
        case 4:
            viewList(DATA_FILE_NAME);
            break;
        default:
            printf("Option must be between 0 and 4\n\n");
        }
    }
}


