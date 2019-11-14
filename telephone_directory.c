#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct directory_info{
    char name[20];
    char number[3][12];
} directory_info_t;
int find_free(directory_info_t *str){
    for(int i=0;i<50;i+=1){
        if(str[i]->name[0]=='\0')
            return i;
    }
    return 0;
}
void browse(directory_info_t* str){
    for(int i=0; str[i]->name[0]!='\0';i++){
        printf("%d.\nContact Name : %s\n",i+1,str[i]->name);
        for(int j=0;str[i]->number[j];j++)
            printf("Contact Number %d = %s \n",j+1,str[i]->number[j]);
    } 
}
int main(){
    directory_info_t file[50];
    char ch;
    while(1){
        printf("What do you want to do?\n1.Add Name\n2.Delet contact\n3.Search(by name)\n4.Browse\n5.Quit\nYour Choice= ");
        scanf("%c",&ch);
        if(ch == '5')
            break;
        switch(ch){
            case '1' :{
                int k=find_free(file);
                printf("Enter name:");
                scanf("%[^\n]s",(file + k)->name);
                for(int i=0;i<3;i++){
                    printf("Enter number %d :",i+1);
                    scanf("%[^\n]s",(file + k)->number[i]);
                }
            };break;
            case '2' :{
                char str[20]; 
                printf("Enter contact name: ");
                scanf("%[^\n]s",str);
                for(int i=0;i<50;i++){
                    if(!strcmp(str,(file + i)->name){
                        (file + i)->name[0] = '\0';
                        break;
                    }
                }
            };break;
            case '3': {
                
            }
        }
        
    
}
