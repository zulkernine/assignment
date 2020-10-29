#include<stdio.h>
#include<string.h>
int strend(char *s, char*t){
    for(int i=(strlen(s) -1),j=(strlen(t) -1);j>=0;j--,i--){
        if(s[i]!=t[j])
            return 0;
    }
    return 1;
}
int main(){
    char s[30],t[30];
    printf("Enter two strings in two different line:\n");
    scanf("%[^\n]s",s);
    getchar();
    scanf("%[^\n]s",t);
    if(strend(s,t)){
        printf("string %s is at the end of %s\n",t,s);     
    }else
        printf("string %s is NOT at the end of %s\n",t,s);
    return 0;
}
