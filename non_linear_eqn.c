#include<stdio.h>
#include<math.h>
#include<stdlib.h>
float f(float x){
    return pow(x,3) -x -2;
}
float df(float x){
    return 3*pow(x,2) -1;
}
float absolute(float x){
    return x>0 ? x : -x ;
}
void Bisection(){
    float x0,x1,e,x2;
    int n;
    float y1,y0,y2;
    printf("Enter value of lower bound x0: ");
    scanf("%f",&x0);
    printf("Enter value of upper bound x1: ");
    scanf("%f",&x1);
    printf("Enter value of max value of error of root: ");
    scanf("%f",&e);
    printf("Enter value of max iteration: ");
    scanf("%d",&n);
    y0 = f(x0); y1 = f(x1);
    printf("\n");
    for(int i=0;i<n;i+=1){
        x2 = ( x0 + x1)/2 ;
        y2 = f(x2);
        if(absolute(y2) < e){
            printf("Convergent solution. Approx. Root: %f\t f(%f) = %f\nNumbe of iteration =%d\n",x2,x2,y2,i+1);
            return ;
        }
        //test
        //    printf("%f\t",y2);
        if( y0*y2 > 0){
            x0 = x2;
            y0 = y2;
        }else{
            x1 = x2;
            y1 = y2;
        }
    }
    printf("Solution doesn't converged in %d iteration. x2 = %f \t y2 = %f \n",n,x2,y2);    
}
void Newton_rapson(){
    float x0,e,delta,n;
    printf("Enter the value of intial guess: ");
    scanf("%f",&x0);
    printf("Enter the value of max error: ");
    scanf("%f",&e);
    printf("Enter the value of Delta(minimum value of the slope) : ");
    scanf("%f",&delta);
    printf("Enter the value of max iteration: ");
    scanf("%f",&n);
    float dy0,x1,y0;
    printf("\n");
    for(int i=0;i<n;i+=1){
        y0 = f(x0);
        dy0 = df(x0);
        if(absolute(dy0)<delta)
            printf("Slope too small. current approx root = %f \t f(%f) = %f \n",x0,x0,y0);
        x1 = x0 - y0/dy0 ;
      if(f(x1)<e){
            printf("Convergant solution. Approx. root = %f . f(%f) = %f \nNumber of iteration=%d\n",x1,x1,f(x1),i+1);
            return;
        }
        x0 = x1;
    }
    printf("Solution didn't converged. appprox root obtained = %f\tf(%f)=%f\n",x0,x0,f(x0));
    return;
    
}
void Regular_falsi(){
    float x0,x1,x2,e,n;
    float y0,y1,y2;
    printf("Enter value of lower bound x0: ");
    scanf("%f",&x0);
    printf("Enter value of upper bound x1: ");
    scanf("%f",&x1);
    printf("Enter value of max value of error of root: ");
    scanf("%f",&e);
    printf("Enter value of max iteration: ");
    scanf("%f",&n);   
    y0 = f(x0);
    y1 = f(x1);
    printf("\n"); 
    for(int i=0;i<n;i++){
        x2 = ( x0 * y1 - x1*y0)/(y1-y0);
        y2 = f(x2);
        if(absolute(y2)<e){
            printf("Converge solution. Approx root = %f \t f(%f) = %f\n",x2,x2,y2);
            return;
        }
        if(y0*y2<0){
            x1 = x2;
            y1 = y2;
        }else{
            x0 = x2;
            y0 = y2;
        }
    }
    printf("Solution does not converged. Approx root = %f \t f(%f) = %f\n",x2,x2,y2);
    return;
}
int main(){
    printf("Choose Method\n1. Bisection Method\n2. Newton-Rapson Method\n3. Regulsr-falsi Method\n");
    int ch;
    printf("Enter your choice:");
    scanf("%d",&ch);
    switch(ch){
        case 1: Bisection();break;
        case 2: Newton_rapson();break;
        case 3: Regular_falsi();break;
    }
    return 0;
}
