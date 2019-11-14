#include<stdio.h>
#include<stdlib.h>
void rev_word(char *str, int n1, int n2){
    char ch;
    int n = n2 - n1 - 1;
    for(int i= n1+1;i<n2;i++,n2--){
        ch = str[i];
        str[i]=str[n2-1];
        str[n2-1] = ch;
    }
}
int main(){
    int space_position[50]={-1};
    char str[150];
    printf("Enter the string:");
    scanf("%[^\n]s",str);
    for(int i=0,j=1;i<150;i++){
        if(str[i]==' '||str[i]=='\0'){
            space_position[j]=i;
            j+=1;
        }
    }
    for(int i=0;space_position[i+1];i++){
        rev_word(str,space_position[i],space_position[i+1]);
    }
    printf("%s\n",str);    
}
