#include<stdio.h>
void main(){
    char vowel[10]={'a','e','i','o','u','A','E','I','O','U'};
    char text[100];
    int count=0;
    printf("Enter text(within 100 charecter) =");
    scanf("%[^\n]s",text);
    for(int i=0;text[i+1];i++){
        int succesion =0;
        for(int j=0;vowel[j];j++){
            if(text[i]==vowel[j])
                succesion += 1;
            if(text[i+1]==vowel[j])
                succesion += 1;
            
        }
        if(succesion==2)
            count += 1;
    }
    printf("Number of ocurance of any two vowel in succesion = %d\n",count); 

}
