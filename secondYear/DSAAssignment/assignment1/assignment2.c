/*
    Write a program to generate the nth Fibonacci number iteratively and recursively.
    Check when there is overflow  in  the  result  and  change  the  data  types  for 
    accommodating  higher  values  of  inputs.  Plot  the  Fibonacci number vs n graph.
*/

#include<stdio.h>
#define ll long long

ll fibonacciIteratively(ll num){
    if(num<=2 && num>0){
        return 2;
    }else if(num>2){
        int prev1=1,prev2=1;
        ll finacciNum=0;
        for(int i=3;i<=num;i++){
            finacciNum = prev1+prev2;

            prev1 = prev2;
            prev2 = finacciNum;
        }
        return finacciNum;
    }
}

ll fibonacciRecursive(ll num){
    if(num == 1) return 1;
    else if(num == 2) return 1;
    else return (fibonacciRecursive(num-1) + fibonacciRecursive(num-2));
}

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d",&num);

    ll fibNum;
    fibNum = fibonacciIteratively(num);
    printf("Iterative computation of %d = %lld\n\n",num,fibNum);

    if(num>43){
        printf("Number is too big to compute recursively. :)\n\n");
    }else{
        fibNum = fibonacciRecursive(num);
        printf("Recursive computation of %d = %lld\n\n", num, fibNum);
    }
}

