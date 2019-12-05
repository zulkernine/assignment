#include<stdio.h>
#include<stdlib.h>
float **a;
int n;
float *x;
//void Jacobian();
//void GE_pivot();
void input(){
    printf("variabe number = ");
    scanf("%d",&n);
    printf("you must enter %d equations. Coefficient should be space separated . ",n);
    a = (float**)malloc(n*sizeof(float*));
    x = (float*)malloc(n*sizeof(float));
    for(int i=0;i<n;i++){
        *(a+i) = (float *)malloc((n+1)*sizeof(float)); 
        for(int j=0;j<n+1;j++)
            scanf("%f",*(a+i)+j);
    }
}
void output(){
    printf("Solution:\n");
    for(int i=0;i<n;i++)
        printf("%.3f\t",x[i]);
    printf("\n");
}
void Gauss_Elimination(){
    input();
    //elimination
    float u;
    for(int k=0;k<n-1;k++){
        for(int i=k+1;i<n;i++){
            u = a[i][k]/a[k][k];
            for(int j=k;j<n+1;j++)
                a[i][j] -= u*a[k][j]; 
        }
    }
    //backward
    float sum=0;
    x[n-1] = a[n-1][n]/a[n-1][n-1];
    for(int i = n-2;i>=0;i--){
        sum=0;
        for(int j=i+1;j<n;j++){
            sum += a[i][j]*x[j];
        }
        x[i] = (a[i][n] - sum)/a[i][i];
    }
    output();
}

int main(){
    printf("Choose Method\n1. Gauss_Elimination\n2. Jacobian\n3. GE_pivot\n");
    int ch;
    printf("Enter your choice:");
    scanf("%d",&ch);
    switch(ch){
        case 1: Gauss_Elimination();break;
        //case 2: Jacobian();break;
        //case 3: GE_pivot();break;
    }
    return 0;
}

