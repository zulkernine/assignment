#include <stdio.h>
#include <stdlib.h>
float **a;
int n;
float *x;
void Jacobian(){
    input();
    float error,*temp_x;
    int maxit;
    temp_x = (float *)malloc(n * sizeof(float));
    printf("Max error = ");
    scanf("%f",&error);
    printf("Max iteration = ");
    scanf("%d",&maxit);
    for(int i=0;i<n;i++)
        x[i] = 0 ;
    for(int iter=1;iter<=maxit;iter+=1){
        //test
            printf("iter = %d\n",iter);
        float big =0,relerror;
        for(int i=0;i<n;i+=1){
            float sum=0;
            for(int j=0;j<n;j+=1)
                if(i!=j)
                    sum += a[i][j]*x[j];
            float temp = (a[i][n]-sum)/a[i][i];
            relerror = (x[i]-temp)/temp;
            relerror = (relerror>0) ? relerror : -1*relerror;
            if(relerror>big)
                big = relerror;
            temp_x[i] = temp;
        }
        for(int i=0;i<n;i++)
            x[i] = temp_x[i] ;
        if(big<error){
            printf("Solution converges.\n");
            output();
            return;
        }
        output();
    }
    printf("Does not converge in maxit number of iterations. Increase number of iteration to get more accurate solution. Current solution is following:\n");
    output();
    return;
}
void GE_pivot(){
    input();
    int j;
    float f;
    for(int i=0;i<n;i+=1){
        j=i;
        float in_ch;
        while(a[i][j] == 0 && j<n){
            for(int l=0;l<n+1;l+=1){
                in_ch = a[i][l];
                a[i][l] =a[j+1][l];
                a[j+1][l] = in_ch; 
            }
            j+=1;
        } 
        f = a[i][i];
        for(int k=0;k<n+1;k+=1)
            a[i][k] /= f; 
        for(int k=0;k<n;k+=1){
            if(k!=i){
                f = a[k][i]/a[i][i];
                for(int p=0;p<n+1;p+=1)
                    a[k][p] = a[k][p] - f * a[i][p];
            }
        }
    }
    for(int i=0;i<n;i+=1)
        x[i] = a[i][n];
    output();

}
void input(){
    printf("variabe number = ");
    scanf("%d", &n);
    printf("you must enter %d equations. Coefficient should be space separated . ", n);
    a = (float **)malloc(n * sizeof(float *));
    x = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++){
        *(a + i) = (float *)malloc((n + 1) * sizeof(float));
        for (int j = 0; j < n + 1; j++)
            scanf("%f", *(a + i) + j);
    }
}
void output(){
    printf("Solution:\n");
    for (int i = 0; i < n; i++)
        printf("%f\t", x[i]);
    printf("\n");
}
void Gauss_Elimination(){
    input();
    //elimination
    float u;
    for (int k = 0; k < n - 1; k++){
        for (int i = k + 1; i < n; i++){
            u = a[i][k] / a[k][k];
            for (int j = k; j < n + 1; j++)
                a[i][j] -= u * a[k][j];
        }
    }
    //backward
    float sum = 0;
    x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--){
        sum = 0;
        for (int j = i + 1; j < n; j++){
            sum += a[i][j] * x[j];
        }
        x[i] = (a[i][n] - sum) / a[i][i];
    }
    output();
}

int main(){
    printf("Choose Method\n1. Gauss_Elimination\n2. Jacobian\n3. GE_pivot\n");
    int ch;
    printf("Enter your choice:");
    scanf("%d", &ch);
    switch (ch){
        case 1:
        Gauss_Elimination();
        break;
        case 2: Jacobian();break;
        case 3: GE_pivot();break;
    }
    return 0;
}
