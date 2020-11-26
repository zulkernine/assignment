/*
    Write a program to generate 1,00,000 random strings of capital letters of length 10 each,
    without repetitions and store them in a file in character mode one string  per line
*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#define mod(x) (x)>0 ? (x) : (-x)
#include <stdint.h>

uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;

void initRandGen(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    s *= ts.tv_nsec;
}
inline static uint32_t msws() {
    x *= x;
    x += (w += s);
    return x = (x >> 32) | (x << 32);
}
long long getRandomNumber(long long range){
    long long rand = msws();
    rand = mod(rand);
    rand %= range;

    return rand;
}

void fillWithRandomString(char*str,int size){
    char num;
    for(int i=0;i<size;i++){
        num = 65 + getRandomNumber(26);
        str[i] = num;
    }
    str[size] = '\0';
}


int main(){
    initRandGen();
    int size=10;
    char string[11] = "";
    FILE *output;

    if((output = fopen("random_string.txt","w")) == NULL){
        printf("Can't create file. :( \n");
    }

    for(int i=0;i<100000;i++){
        fillWithRandomString(string,size);
        fprintf(output,"%s\n",string);
    }

    fclose(output);

    return 0;
}
