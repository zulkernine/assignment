/*
    Write a program to compute the factorial of an integer n iteratively and recursively.
    Check when there is overflow in the result and change the data types for accommodating
    higher values of inputs.
*/

//Using Built in data type

#include<stdio.h>
#define LL long long 

LL factorialIteratively(LL num){
    LL product = 1;
    for (LL i = num;i > 1;i--) product *= i;

    return product;
}

LL factorialRecursive(LL num){
    if (num <= 2) return num;

    return num * factorialRecursive(num - 1);
}

LL main(){
    LL num;
    printf("Enter an integer: ");
    scanf("%lld", &num);

    LL factorial;
    factorial = factorialIteratively(num);
    printf("Iterative computation of factorial: %lld\n\n", factorial);

    factorial = factorialRecursive(num);
    printf("Recursive computation of factorial: %lld\n\n", factorial);

    return 0;
}

