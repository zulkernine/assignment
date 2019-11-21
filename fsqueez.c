#include<stdio.h>
#include<stdlib.h>
void squeeze(char*s,char ch){
    int k=0,j;
    for( j=0; s[j+k] ; j+=1){
        if(s[j+k]==ch)
            k += 1;
        s[j] = s[j+k];
    }
    s[j] = '\0';
}
int main(){
    char str[30],ch;
    printf("Enter the string:");
    scanf("%[^\n]s",str);
    getchar();
    printf("Enter the charecter: ");
    scanf("%c",&ch);
    squeeze(str,ch);
    printf("Formatted string: %s\n",str);
    return 0;
}
