#include<stdio.h>
#include<stdlib.h>
void convert(int n,char*s,int w){
    char str[15];
    int i=0;
    while(n>0){
        str[i] = 48 + n%10 ;
        n /= 10 ;
        i+=1;
    }
   s[w-1]='\0';
    for(int j=w-2,k=0;k<w;j--,k++){
        if(str[k])
            s[j]=str[k];
        else
            s[j]=' ';
    }
}
int main(){
    int n,w;
    char*s;
    printf("Enter the number=");
    scanf("%d",&n);
    printf("Enter string width=");
    scanf("%d",&w);
    s=malloc(w*sizeof(char));
    convert(n,s,w+1);
    printf("string number is : %s\n",s);
    return 0;
}
