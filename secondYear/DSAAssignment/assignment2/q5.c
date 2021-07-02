#include<stdio.h>
#include "c_string.h"

int main(){
    char str1[50] = "This is a string";
    char str2[20] = "This is another";

    printf("String-1: %s \t String-2: %s\n",str1,str2);
    printf("Length of str1: %d\nLength of str2:%d\n",string_length(str1),string_length(str2));
    printf("comparison of two string: %d\n",string_cmp(str1,str2));
    string_upper(str1);
    printf("Upper case: %s\n",str1);
    string_lower(str2);
    printf("Lower case: %s\n",str2);
    string_concat(str1,str2);
    printf("Concatenation: %s\n",str1);
    string_copy(str2,str1);
    printf("Copy: %s\n",str1);

    return 0;
}
