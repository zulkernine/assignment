#include <stdio.h>
#include <string.h>

int main(){
    int n;
    printf("Enter number of student=");
    scanf("%d",&n);
    char student_name[2][20],pf[2][5];
    int marks[2][5],total[2]={0},percentage[2],fail[2];
    char grade[2][5],class[2];
    char sub[][10]={"Phys.","Chemist.","Math","Geo.","Hist."};
    for(int i=0;i<2;i++){
        printf("Enter student name:");
        scanf("%s",student_name[i]);
        for(int j=0;j<5;j++){
            printf("Enter the marks of %s=",sub[j]);
            scanf("%d",&marks[i][j]);
        }
    }
   
    for(int i=0;i<2;i++){
        int sf=0;
        for(int j=0;j<5;j++){
            total[i] += marks[i][j];
            if(marks[i][j]<40){
                sf+=1;
            }    
        }
        percentage[i] = total[i]/5 ;
        if(percentage[i]>=60)
            class[i]= 'a';
        else if(percentage[i]<60 && percentage[i] >= 50)
            class[i]= 'b' ;
        else
            class[i]= 'c' ;
        switch(class[i]){
            case 'a':{
                if(sf<=3){
                    for(int j=0;j<5;j++){
                        if(marks[i][j]<40)
                            marks[i][j] += 5;
                    }
                }
            };break;
            case 'b':{
                if(sf<=2){
                    for(int j=0;j<5;j++){
                        if(marks[i][j]<40)
                            marks[i][j] += 4;
                    }
                }
            };break;
            case 'c':{
                if(sf<=1){
                    for(int j=0;j<5;j++){
                        if(marks[i][j]<40)
                            marks[i][j] += 5;
                    }
                }
            };break;   
        }
      
        total[i]=0;
        for(int j=0;i<5;i++)
                total[i]+=marks[i][j];
        percentage[i] = total[i]/5 ;
        if(percentage[i]>=50)
            strcpy( pf[i],"Pass");
            //pf[i]= "Pass";
        else
            strcpy(pf[i],"Fail");
            // pf[i]= "Fail";       
        printf("status= %s",pf[i]);
        if(percentage[i]>=65)
            class[i]= 'A';
        else if(percentage[i]<60 && percentage[i] >= 50)
            class[i]= 'B' ;
        else
            class[i]= 'F' ;
        printf("over all grade %c \n",class[i]);
        for(int j=0;j<5;j++){
            if(marks[i][j]<40)
                grade[i][j]='F';
            else if(marks[i][j]<60&&marks[i][j]>=40)
                grade[i][j]='C';
            else if(marks[i][j]<80&&marks[i][j]>=60)
                 grade[i][j]='B';
            else if(marks[i][j]<90&&marks[i][j]>=80)
                 grade[i][j]='A';
            else if(marks[i][j]>=90)
                 grade[i][j]='s'; 
             printf("%c    \n",grade[i][j]);   
        }
      
        
    }
    /*for(int i=0; i<2;i++){
        printf("Name: %s\n",student_name[i]);
        printf("Subject\t\t\tMarks\t\t\tGrade\n");
        for(int j=0;j<5;j++){
            printf("%s\t\t\t%d\t\t\t%c\n\n",sub[j],marks[i][j],grade[i][j]);
        }
        printf("Status:%s\n",pf[i]);
        printf("Over all Grade :%c",class[i]);
        printf("\n\n");
    }
    */
    
    return 0;
}
