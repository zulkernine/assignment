/*
    Store the names of your classmates according to roll numbers in a text file one
    name per line. Write a program to find out from the file, the smallest and largest
    names and their lengths in number of characters.Write a function to sort the
    names alphabetically and store in a second file.
*/

#include<stdio.h>
#include<stdlib.h>

int stringLentgh(char* str){
    int length=0;
    while(str[length] != '\0') length++;
    return length;
}

int noOfLines(char* filename){
    FILE *fn = fopen(filename,"r");
    if(fn == NULL){
        printf("Can't open file :(\n");
        exit(1);
    }

    char bf[100];int count=0;
    while(!feof(fn)){
        fgets(bf,100,fn);
        count++;
    }
    fclose(fn);
    return count;
}

void stringCopy(char *dest,char *source){
    int i=0;
    
    do{
        dest[i] = source[i];
    } while (source[i++] != '\0');
}

int main(){
    char buff[100];

    //Get the file name
    printf("Enter the names' file name: ");
    scanf("%s",buff);

    int numberOfnames = noOfLines(buff);

    //Load the names in a name array in main memory
    char** names;
    names = (char**)malloc(sizeof(char*) * numberOfnames);
    FILE* input = fopen(buff, "r");
    for(int i=0;i<numberOfnames;i++){
        fgets(buff,100,input);
        names[i] = (char*)malloc( sizeof(char) * (stringLentgh(buff) + 1));
        stringCopy(names[i],buff);
    }
    fclose(input);

    //sol1: print the smallest and longest name with length:
    char *smallestName = names[0], *longestName = names[0];
    int smallestNameLength = stringLentgh(smallestName),longestNameLength = stringLentgh(longestName);

    for(int i=1;i<numberOfnames;i++){
        int len = stringLentgh(names[i]);

        if(len<smallestNameLength){
            smallestNameLength = len;
            smallestName = names[i];
        }else if(len > longestNameLength){
            longestNameLength = len;
            longestName = names[i];
        }
    }

    printf("Longest name in given file: %sLength:%d\n", longestName, longestNameLength);
    printf("Smallest name in given file: %sLength:%d\n", smallestName, smallestNameLength);

    return 0;
}

