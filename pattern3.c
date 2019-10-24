#include <stdio.h>
void main(){
    int n;
    printf("Enter a number=");
    scanf("%d",&n);
    for(int i=0;i< n/2 +1;i++) {
        for(int j=n-i;j>=i;j--)
            printf("%d ",j);
        printf("\n");
    }
}
