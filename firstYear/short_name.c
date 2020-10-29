#include<stdio.h>
#include<ctype.h>
void main(){
    char name[4][15];
    printf("Enter the full name (space separated) =");
    for(int i=0;;i++){
        scanf("%s",name[i]);
        if(getchar()=='\n')
            break;
    }
    printf("Short name = ");
    for(int i=0;name[i][0];i++){
        printf("%c",toupper(name[i][0]));
        //test
        //printf("\n%s\n",name[i]);
    }
    printf("\n");
}    
   
