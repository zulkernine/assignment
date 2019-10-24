#include<stdio.h>
void swap(int*m,int*n){
    int t;
    t=*m;
    *m=*n;
    *n=t;
}

int num(int n[4]){
    int number=0;
    for(int i=0;i<4;i++)
        number += n[i];
    return number;
}
void num_to_arr(int n,int arr[4]){
    int i=0;
    while(n>0){
        arr[i]=n%10;
        n=n/10;
        i++;
    }
}
void sort_min(int n[4]){
    for(int i=0;i<4;i++){
        for(int j=i;j<4;j++){
            if(n[j]<n[j+1])
                swap(&n[j],&n[j+1]);
        }
    }
}
void reverse(int n1[4],int n2[4]){
    for(int i=0,j=3;i<4;i++,j--)
        n2[j]=n1[i];
}
int main(){
    int N,big[4],small[4],N_arr[4];
    N=2462;
    num_to_arr(N,N_arr);
    sort_min(N_arr,small);
    reverse(small,big);
    printf("%d\n%d",num(small),num(big));
    return 0;
}

