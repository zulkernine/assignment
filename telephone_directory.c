#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct directory_info{
    char name[20];
    char number[3][12];
} directory_info_t;
int find_free(directory_info_t *str){
    for(int i=0;i<50;i+=1){
        if(str[i].name[0]=='\0')
            return i;
    }
    return 0;
}
void browse(directory_info_t*str){
    printf("\n---------------------------------\nPRINTING CONTACT INFORMATION:\n");
    for(int i=0;i<50;i++){
        if(str[i].name[0]!='\0'){
        printf("%d.\nContact Name : %s\n",i+1,str[i].name);
        for(int j=0;j<3;j++)
            if(str[i].number[j][0]!='\0')
                printf("Contact Number %d = %s \n",j+1,str[i].number[j]);
            else 
                break;
        }
        else
            break;        
        printf("-------------------------------\n");
    } 
}
int main(){
    directory_info_t file[50];
    //initialise the structure
    for(int i=0;i<50;i++){
        file[i].name[0]='\0';
        file[i].number[0][0]='\0';
        file[i].number[1][0]='\0';
        file[i].number[2][0]='\0';
    }
    char ch;
    while(1){
        printf("What do you want to do?\n1.Add Name\n2.Delet contact\n3.Search(by name)\n4.Browse\n5.Quit\nYour Choice= ");
        //scanf("%c",&ch);
        while((ch=getchar())=='\n');
        getchar();
        switch(ch){
            case '1' :{
                int k=find_free(file);
                printf("Enter name:");
                scanf("%[^\n]s",(file + k)->name);
                getchar();
                for(int i=0;i<3;i++){
                    printf("Enter number %d :",i+1);
                    scanf("%[^\n]s",(file + k)->number[i]);
                    getchar();
                }
            };break;
            case '2' :{
                char str[20]; 
                printf("Enter contact name: ");
                scanf("%[^\n]s",str);
                for(int i=0;i<50;i++){
                    if(!strcmp(str,(file + i)->name)){
                        (file + i)->name[0] = '\0';
                        break;
                    }
                }
            };break;
            case '3': {
                char sname[20];
                for(int i=0;i<50;i++){
                    if(!strcmp(sname,file[i].name)){
                        printf("Number of %s is:\n",file[i].name);
                        for(int j=0;file[i].number[j];j++)
                            printf("%s\n",file[i].number[j]);
                        break;
                    }
                }                
            };break;
            case '4':browse(file);break;
            case '5':exit(0);break;
        }
    }
    return 0;     
}
