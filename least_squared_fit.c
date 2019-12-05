#include<stdio.h>
#include<stdlib.h>
float sum_x(float *num,int size){
    float sum=0;
    for(int i=0;i<size;i++)
        sum  += num[i];
    return sum;
}
float sum_xy(float **num,int size){
    float sum=0;
    for(int i=0;i<size;i++)
        sum += num[0][i] * num[1][i] ;
    return sum;
} 
float sum_x2(float *num,int size){
    float sum=0;
    for(int i=0;i<size;i++)
        sum  += num[i]*num[i];
    return sum;
}
void input_data(float **num, int size){
    for(int i=0;i<size;i++){
        printf("value of x%d = ",i+1);
        scanf("%f",*num+i);
        printf("value of y%d = ",i+1);
        scanf("%f",*(num+1)+i);        
    }
}
int main(){
    float a1,a0;
    int size;
    float **num_data;
    printf("Enter the size of data: ");
    scanf("%d",&size);
    num_data = (float **)calloc(2,sizeof(float*));
    for(int i=0;i<2;i++) *(num_data + i) = (float *)calloc(size,sizeof(float));
    printf("Enter the data:\n");
    input_data(num_data,size);
    //
    a0 = (sum_x(num_data[1],size)*sum_x2(num_data[0],size) - sum_x(num_data[0],size)*sum_xy(num_data,size))/(size*sum_x2(num_data[0],size)- sum_x(num_data[0],size)*sum_x(num_data[0],size)) ;
    //
    a1 = (size*sum_xy(num_data,size)-sum_x(num_data[0],size)*sum_x(num_data[1],size))/(size*sum_x2(num_data[0],size)- sum_x(num_data[0],size)*sum_x(num_data[0],size)) ;
    //
    printf("REgression coefficient:\n a0 = %f \t a1 = %f \n",a0,a1);
    printf("Regression Line: y = %fx + %f\n",a1,a0);
    return 0;
}
