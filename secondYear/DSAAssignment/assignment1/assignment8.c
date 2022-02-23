/*
    Convert your Name and Surname into large integers by juxtaposing integer ASCII
    codes for alphabet. Print the corresponding converted integer. Cut the large
    integers into two halves and add the two halves. Compute the remainder after
    dividing the by the prime numbers P in problem 7
*/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct{
    char quotient[MAX_SIZE];
    int remainder;
}answer;

int len(char* str){
    int l = 0;
    while (str[l]) l++;
    return l;
}

answer longDevision(char* num,int divisor){
    answer ans;
    int idxNum=0,idxAns=0;
    ans.remainder = num[idxNum++] - '0';
    while (ans.remainder < divisor){
        ans.remainder = ans.remainder * 10 + (num[idxNum++] - '0');
    }

    int numLenth = len(num);

    while (1){
        ans.quotient[idxAns++] = ans.remainder / divisor + '0';
        ans.remainder = (ans.remainder % divisor) ;

        if (idxNum < numLenth){
            ans.remainder = (ans.remainder ) * 10 + num[idxNum++] - '0';
        }else break;
    }

    ans.quotient[idxAns]='\0';

    return ans;

}

void sumArr(int* result, int* operand1, int* operand2){
    int buf = 0;
    for (int i = MAX_SIZE - 1;i >= 0;i--){
        int temp = operand1[i] + operand2[i] + buf;

        result[i] = temp % 10;
        buf = temp / 10;
    }

    if (buf > 0){
        printf("Sum is too big. Array overflowed :)\n\n");
        exit(1);
    }
}

char* nameToNumberString(char* name){
    char* str = (char*) malloc(MAX_SIZE * sizeof(char));
    int index=MAX_SIZE-1;
    str[index--]='\0';

    int length = len(name);
    for(int i=length-1;i>=0;i--){
        int d = name[i];
        do{
            str[index--] = d % 10 + '0';
            d /= 10;
        }while(d);
    }
    index++;
    for(int i=0;i+index < MAX_SIZE;i++){
        str[i] = str[i+index];
    }
   
   return str;
}

int main(){
    char name[MAX_SIZE];
    int primes[7] = {
        2153,
        3319,
        4909,
        5849,
        6197,
        7841,
        1459
    };
    printf("Name: ");
    scanf("%[^\n]s",name);

    char* num = nameToNumberString(name);
    printf("Corresponding number: %s\n",num);

    for(int i=0;i<7;i++){
        printf("Prime:%d   ",primes[i]);
        answer ans = longDevision(num,primes[i]);
        printf("Remainder:%d\n",ans.remainder);
    }
    return 0;
}

