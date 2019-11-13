#include<stdio.h>
int is_vowel(char ch){
    char vowel[10]={'a','e','i','o','u','A','E','I','O','U'};
    for(int i=0;i<10;i++){
        if(ch == vowel[i])
        return 1;
    }
    return 0;
}
void main(){
    char text[100];
    int count=0;
    printf("Enter text(within 100 charecter) =");
    scanf("%[^\n]s",text);
    for(int i=0;text[i+1]!='\0';i++){
        if(is_vowel(text[i])&&is_vowel(text[i+1]))
            count += 1;
    }
    printf("Number of ocurance of any two vowel in succesion = %d\n",count);
}
