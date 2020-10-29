/*
    Write a program that will have an integer variable and a pointer (say, p) pointing to it. 
    Also have a pointer to pointer pointing to p.
    Take the value for the integer variable and print it using p, and pp.
*/

#include<stdio.h>
int main(){
    int d,*p,**pp;
    p = &d;
    pp = &p;

    printf("Enter the number:");
    scanf("%d",p);

    printf("Number printed using variable: %d\n",d);
    printf("Number printed using pointer to variable: %d\n", *p);
    printf("Number printed using pointer to pointer to variable: %d\n", **pp);
    return 0;
}