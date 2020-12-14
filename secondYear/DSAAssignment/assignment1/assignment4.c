#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000

int main(){
    //Initialise File pointer
    FILE *output;
    if((output=fopen("random_number2.txt","w"))==NULL){
        printf("Can't open file :(\n");
        exit(1);
    }

    //Init srand using current nanosecond
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);

    //To avoid repitation,an array is used 
    int arr[SIZE + 1]={0};
    int count = 100000,itr=0;

    while(count){
        int temp = rand()%(SIZE+1) ;
        if(arr[temp]==0){
            arr[temp]=1;
            fprintf(output, "%d\n", temp);
            --count; //When all numbers are generated,count becomes 0
        }
        itr++; //It counts how many times this loop is continued
    }
    fclose(output);
    printf("Number of iteration:%d\n",itr);
    printf("RAND_MAX:%d\n",RAND_MAX);
    return 0;
}

