#include<stdio.h>
#include<stdlib.h>
char*str_alt(char*str1,char*str2){
    static char str3[100];
    int i=0,j=0,k=0;
    for(i;str1[j]||str2[k];i++){
        if(i%2==0 && str1[j]){
            str3[i] = str1[j];
            j++;
        }else if( i%2 ==0 && !str1[j] ){
            str3[i] = str2[k];
            k++;
        }
        if(i%2!=0 && str2[k]){
            str3[i] = str2[k];
            k++;
        }else if( i%2!=0 && !str2[k] ){
            str3[i] = str1[j];
            j++;
        }
    }
    str3[i]='\0';
    return str3;
}
int main(){
    char str1[50],str2[50];
    printf("Enter the first string:");
    scanf("%[^\n]s",str1);
    //fflush(stdout);
    while(getchar()!='\n');
    //printf("%s\n",str1);
    printf("Enter second string:");
    scanf("%[^\n]s",str2);
    //gets(str2);
    //printf("%s\n",str2);
    
    printf("new string = %s\n",str_alt(str1,str2));
    return 0;
}
