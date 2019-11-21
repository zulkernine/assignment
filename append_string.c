#include<stdio.h>
#include<stdlib.h>
char *str_append(char*s1,char*s2,int i){
    char* s3=malloc(60*sizeof(char));
    int j=0;
    if(!s3){
        printf("Exit");
    }
    for(int k=0; s2[k] != '\0' ; j++){
        if(j<i){
            s3[j] = s1[j];
       }
        else{
            s3[j] = s2[k];
            k += 1;
       }
    }
    s3[j] = '\0';
   return s3;
}
int main(){
    char str1[30],str2[30];
    char* str3;
    str3 = malloc(60*sizeof(char));
    if(!str3){
        printf("Exit");
    }
    int i;
    printf("Enter first string:");
    scanf("%[^\n]s",str1);
    getchar();
    printf("Enter second string:");
    scanf("%[^\n]s",str2);
    printf("Enter the number=");
    scanf("%d",&i);
    str3 = str_append(str1,str2,i);
    printf("New string:%s\n",str3);
    return 0;
}
