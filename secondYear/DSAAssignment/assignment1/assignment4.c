#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#define mod(x) (x)>0 ? (x) : (-x)
#include <stdint.h>

uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;
// uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;

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

int main(){
    FILE *output;
    if((output=fopen("random_number.txt","w"))==NULL){
        printf("Can't open file :(\n");
        exit(1);
    }
    initRandGen();

    for (int i = 0;i < 100000;i++){
        int temp = (int) getRandomNumber(100000);

        fprintf(output, "%d\n", temp);
    }

    fclose(output);

    return 0;
}

