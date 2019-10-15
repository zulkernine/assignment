#include<stdio.h>
#include<stdlib.h>
struct  student_data {
    char name[20];
    int marks[5];
    char grade[5];
    int total_mark;
    float average;
} ;
void data_entry(struct student_data *stu){
    char sub[5][11]={
    "Physics","Chemistry","Math","History","Geography"    
    };
    printf("\n--------------------------------------------------\n");
    //printf("Press enter to insert New Data.");
    printf("Enter the student's name:");
    fflush(stdin);
    scanf("%[^\n]s",stu->name);
    for(int j=0;j<5;j++){
        printf("Enter the number of %s =",sub[j]);
        scanf("%d",&stu->marks[j]);
    }  
    //fflush(stdin);
    while(getchar()!='\n'); 
}
void processing_data(struct student_data *stu){
    int sf=0;
    char class;
        for(int j=0;j<5;j++){
            stu->total_mark += stu->marks[j];
            if(stu->marks[j]<40){
                sf+=1;
            }    
        }
        stu->average = stu->total_mark/5 ;
        if(stu->average>=60)
            class= 'a';
        else if(stu->average<60 && stu->average >= 50)
            class= 'b' ;
        else
            class= 'c' ;
        switch(class){
            case 'a':{
                if(sf<=3){
                    for(int j=0;j<5;j++){
                        if(stu->marks[j]<40)
                            stu->marks[j] += 5;
                    }
                }
            };break;
            case 'b':{
                if(sf<=2){
                    for(int j=0;j<5;j++){
                        if(stu->marks[j]<40)
                            stu->marks[j] += 4;
                    }
                }
            };break;
            case 'c':{
                if(sf<=1){
                    for(int j=0;j<5;j++){
                        if(stu->marks[j]<40)
                            stu->marks[j] += 5;
                    }
                }
            };break;   
        }
      
        stu->total_mark=0;
        for(int j=0;j<5;j++)
                stu->total_mark += stu->marks[j];
        stu->average = stu->total_mark/5 ;
        for(int j=0;j<5;j++){
            if(stu->marks[j]<40)
                stu->grade[j]='F';
            else if(stu->marks[j]<60 && stu->marks[j]>=40)
                stu->grade[j]='C';
            else if(stu->marks[j]<80 && stu->marks[j]>=60)
                stu->grade[j]='B';
            else if(stu->marks[j]<90 && stu->marks[j]>=80)
                stu->grade[j]='A';
            else if(stu->marks[j]>=90)
                stu->grade[j]='S';    
        }
} 
void print_result(struct student_data *stu){
    char sub[5][11]={
    "Physics  ","Chemistry","Math     ","History  ","Geography"    
    };
    printf("\n\n--------------------------------------------------\n");
    printf("Name: %s\n",stu->name);
    printf("SUBJECT\t\tMARRKS(100)\tGRADE\n");
    for(int i=0;i<5;i++){
        printf("%s\t\t%d\t%c\n",sub[i],stu->marks[i],stu->grade[i]);
    }
    printf("\n");
    if(stu->average>=60)
        printf("Passed with 1st Division.\n");
    else if(stu->average>=50&&stu->average<60)
        printf("Passed with 2nd Division.\n");
    else
    {
        printf("Status : FAILED.\n");
    }
    printf("Total marks = %d \t Percentage mark = %2.2f",stu->total_mark,stu->average);
}
int main(){
    struct student_data students[2];
    for(int i=0;i<2;i++){
        data_entry(&students[i]);
        printf("\n");
    }
    printf("Processing the entered data.\n");
    for(int i=0;i<2;i++){
        processing_data(&students[i]);
        printf("\n");
    }
    printf("Processing done.\n");
    for(int i=0;i<2;i++){
        print_result(&students[i]);
        printf("\n");
    }
}          