#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct directory_info{
    char name[20];
    char number[3][12];
} directory_info_t;
void rearrange(directory_info_t *str,int i,int legit){
    str[i] = str[legit-1];
    //delete_contact(str,legit);
    str[legit].name[0]='\0';
    str[legit].number[0][0]='\0';
    str[legit].number[1][0]='\0';
    str[legit].number[2][0]='\0';
}
int find_free(directory_info_t *str){
    for(int i=0;i<50;i+=1){
        if(str[i].name[0]=='\0')
            return i;
    }
    return 0;
}
void browse(directory_info_t*str,int N){
    printf("\n---------------------------------\nPRINTING CONTACT INFORMATION:\n");
    for(int i=0;i<N;i++){
        printf("%d.\nContact Name : %s\n",i+1,str[i].name);
        for(int j=0;j<3;j++)
            if(str[i].number[j][0]!='\0')
                printf("Contact Number %d = %s \n",j+1,str[i].number[j]);
            else 
                break;      
        printf("-------------------------------\n");
    } 
}
int main(){
    directory_info_t file[50];
    int file_size=0;
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
                printf("\n----------------------------------\nADD CONTACT\n");
                int k=find_free(file);
                printf("Enter name:");
                scanf("%[^\n]s",(file + k)->name);
                getchar();
                for(int i=0;i<3;i++){
                    printf("Enter number %d :",i+1);
                    scanf("%[^\n]s",(file + k)->number[i]);
                    getchar();
                }
                file_size += 1;
                printf("\n------------------------------------------\n");
            };break;
            case '2' :{
                printf("\n------------------------------------------\n");
                printf("DELETE CONTACT\n");
                char str[20]; 
                printf("Enter contact name: ");
                scanf("%[^\n]s",str);
                for(int i=0;i<file_size;i++){
                    if(!strcmp(str,(file + i)->name)){
                        //(file + i)->name[0] = '\0';
                        //delete_contact(file,i);
                        rearrange(file,i,file_size);
                        file_size -= 1;
                        break;
                    }
                }
                printf("\n------------------------------------------\n");
            };break;
            case '3': {
                printf("\n------------------------------------------\n");
                printf("SEARCH NAME\n");
                char sname[20];
                printf("Enter the name:");
                scanf("%[^\n]s",sname);
                for(int i=0;i<file_size;i++){
                    if(!strcmp(sname,file[i].name)){
                        printf("Number of %s is:\n",file[i].name);
                        for(int j=0;file[i].number[j][0]!='\0';j++)
                            printf("%s\n",file[i].number[j]);
                        break;
                    }
                }
                printf("\n------------------------------------------\n");                
            };break;
            case '4':browse(file,file_size);break;
            case '5':exit(0);break;
        }
    }
    return 0;     
}
