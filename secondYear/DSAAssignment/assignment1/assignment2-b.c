/*
    Write a program to generate the nth Fibonacci number iteratively and recursively.
    Check when there is overflow  in  the  result  and  change  the  data  types  for
    accommodating  higher  values  of  inputs.  Plot  the  Fibonacci number vs n graph.
*/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1024

void printNum(int* num){
    int start;
    for (int i = 0;i < MAX_SIZE;i++){
        start = i;
        if (num[i] != 0) break;
    }

    while (start < MAX_SIZE) printf("%d", num[start++]);
}

void numToArrayOfDigit(int* ptr, int num){
    for (int i = MAX_SIZE - 1; i >= 0;i--){
        ptr[i] = num % 10;
        num /= 10;
    }
}

void copyArr(int* source, int* dest){
    for (int i = 0;i < MAX_SIZE;i++)
        dest[i] = source[i];
}

void sumArr(int* result, int* operand1, int* operand2){
    int buf = 0;
    for (int i = MAX_SIZE-1;i >=0 ;i--){
        int temp = operand1[i] + operand2[i] + buf;

        result[i] = temp % 10;
        buf = temp / 10;
    }

    if (buf > 0){
        printf("Sum is too big. Array overflowed :)\n\n");
        exit(1);
    }
}

void fibonacciIteratively(int* result,int num){
    if (num <= 2 && num > 0){
        numToArrayOfDigit(result, 1);
    }
    else if (num > 2){
        int prev1[MAX_SIZE], prev2[MAX_SIZE];
        numToArrayOfDigit(prev1, 1);
        numToArrayOfDigit(prev2, 1);
        numToArrayOfDigit(result, 0);

        for (int i = 3;i <= num;i++){
            sumArr(result,prev1,prev2);
            copyArr(prev2,prev1);
            copyArr(result,prev2);
        }
    }
}

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int result[MAX_SIZE];
    fibonacciIteratively(result,num);
    printf("%dth Fibonacci Numer: ",num);
    printNum(result);
    printf("\n\n");
}
