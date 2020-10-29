#include<stdio.h>
int square_sum_of_digit(int n){
    int sum=0;
    while(n>0){
        sum += (n%10)*(n%10);
        n = n/10 ;
    }
    return sum;
}
void main(){
    int N , count=0;
    printf("Enter a number:");
    scanf("%d",&N);
    for(int i=0;count<N;i++){
        int happy_number=i;
        for(int j=0;j<100;j++){
            if(happy_number==1){
                printf("%d\n",i);
                count++;
                break;
            }
            happy_number = square_sum_of_digit(happy_number);
       }
    }            
}
    
