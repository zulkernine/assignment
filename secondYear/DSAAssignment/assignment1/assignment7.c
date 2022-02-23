/*
    Take  a  four-digit  prime  number  P.  Generate  a  series  of  large  integers  L
    and  for  each  member  Li compute  the  remainder  Ri after  dividing  Li by P. 
    Tabulate  Li and Ri.  Repeat  for  seven  other  four  digit  prime numbers keeping Li fixed.
*/

#include<stdio.h>
#include "randomNumgenerator.h"

#define ll long long
#define SIZE 10


void initLargeNumbers(ll* arr,int len){
    for (int i = 0;i < len;i++){
        arr[i] =  s*getRandomNumber(1000000000000000000);
        arr[i] = mod(arr[i]);
    }
}

int main(){
    int primes[7]={
        2153,
        3319,
        4909,
        5849,
        6197,
        7841,
        1459
    };
    ll largens[SIZE];
    initLargeNumbers(largens,SIZE);

    printf("Large Num ↓ prime →");
    for(int i=0;i<7;i++){
        printf("\t\t%d",primes[i]);
    }
    printf("\n");

    for(int j=0;j<SIZE;j++){
        printf("%lld", largens[j]);
        for(int i=0;i<7;i++){
            int remainder;
            remainder = largens[j]%primes[i];

            printf("\t\t%d",remainder);
        }
        printf("\n");
    }

    return 0;
}
