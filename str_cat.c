#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    char str1[50],str2[50],str3[100];
    int i=0,j=0,k=0;
    printf("Enter the first string:");
    scanf("%[^\n]s",str1);
    //fflush(stdout);
    while(getchar()!='\n');
    printf("%s\n",str1);
    printf("Enter second string:");
    scanf("%[^\n]s",str2);
    //gets(str2);
    printf("%s\n",str2);
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
    printf("new string = %s\n",str3);
    return 0;
}
