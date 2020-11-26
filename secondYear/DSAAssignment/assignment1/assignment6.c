/*
    Store the names of your classmates according to roll numbers in a text file one name per line.
    Write a program to find out from the file, the smallest and largest names and their lengths in number of characters.
    Write a function to sort the names alphabetically and store in a second file.
*/

#include<stdio.h>

int main(){
    FILE* input = fopen("nameroll.txt","r");
    FILE* output = fopen("nameroll","w");

    char buff[100];

    while(!feof(input)){
        fscanf(input,"%[^\n]s",buff);
        printf("%s\n",buff);
        fprintf(output,"%s",buff+15);
    }

    fclose(input);fclose(output);

    return 0;
}

