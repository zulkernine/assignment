#include <stdio.h>
#include <string.h>

int main(){
    char student_name[5][20],pf[5][5];
    int marks[5][5],total[5]={0},percentage[5],fail[5];
    char grade[5][5],class[5];
    char sub[][10]={"Physics","Chemistry","Math","Geography","History"};
    for(int i=0;i<5;i++){
        printf("Enter student name:");
        scanf("%s",student_name[i]);
        for(int j=0;j<5;j++){
            printf("Enter the marks of %s=",sub[j]);
            scanf("%d",&marks[i][j]);
        }
    }
   
    for(int i=0;i<5;i++){
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
        
        if(percentage[i]>=65)
            class[i]= 'A';
        else if(percentage[i]<60 && percentage[i] >= 50)
            class[i]= 'B' ;
        else
            class[i]= 'F' ;
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
        }
        
        
    }
    for(int i=0; i<5;i++){
        printf("Name: %s\n",student_name[i]);
        printf("Subject\t\tMarks\t\tGrade\n");
        for(int j=0;j<5;j++){
            printf("%s\t\t%d\t\t%c\n",sub[j],marks[i][j],grade[i][j]);
        }
        printf("Status:%s",pf[i]);
        printf("Over all Grade :%c",class[i]);
    }
    
    
    return 0;
}
