/*
    Write a program to compute the factorial of an integer n iteratively and recursively.
    Check when there is overflow in the result and change the data types for accommodating
    higher values of inputs.
*/

//Using Built in custom data structure
//Only iterative method is used

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 4096

void multiplyNumArr(int* arrNum, int num){
    int buf = 0;
    for (int i = (MAX_SIZE - 1);i >= 0;i--){
        int product = arrNum[i] * num + buf;
        arrNum[i] = product % 10;
        buf = product / 10;
    }

    if(buf){
        printf("Array overflowed :(\nIncrease size of array\n\n");
        exit(2);
    }
}

void numToArrayOfDigit(int* ptr, int num){
    for (int i = MAX_SIZE - 1; num && i >= 0;i--){
        ptr[i] = num % 10;
        num /= 10;
    }
}

void printArrNum(int* ptr){
    int start;
    for (int i = 0;i < MAX_SIZE;i++)
        if (ptr[i]){
            start = i;
            break;
        }

    printf("Number is: ");
    while (start < MAX_SIZE) printf("%d", ptr[start++]);
    printf("\n\n");
}

long long factorialIteratively(long long num){
    long long product = 1;
    for (long long i = num;i > 1;i--) product *= i;

    return product;
}

void factorialIterative(int* arrNum, int num){
    if (num <= 1){
        arrNum[MAX_SIZE - 1] = 1;
    }
    else if (num < 0){
        printf("Negative number!\n\n");
        exit(1);
    }
    else{
        for (int i = 2;i < num;i++){
            multiplyNumArr(arrNum, i);
        }
    }
}



int main(){
    int num;
    int arrNum[MAX_SIZE] = { 0 };
    printf("Enter the number: ");
    scanf("%d", &num);

    if(num<0){
        printf("Please enter a positive integer :(\n\n");
        return 1;
    }

    numToArrayOfDigit(arrNum, num);

    factorialIterative(arrNum, num);

    printf("Iterative computation on array of digit:-\n");
    printArrNum(arrNum);

    long long facto = factorialIteratively(num);
    printf("Iterative factorial using built in data types: %lld\n\n", facto);

    return 0;

}

