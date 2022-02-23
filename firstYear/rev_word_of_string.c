#include<stdio.h>
#include<stdlib.h>
void rev_word(char *str, int n1, int n2){
    char ch;
    for(int i= n1+1;i<n2;i++,n2--){
        ch = str[i];
        str[i]=str[n2-1];
        str[n2-1] = ch;
        //printf("%c\t rf\n",ch);
    }
}
int main(){
    int space_position[50]={[0]=-1},count=1;
    char str[150];
    printf("Enter the string:");
    scanf("%[^\n]s",str);
    for(int i=0;i<150;i++){
        if(str[i]==' '||str[i]=='\0'){
            space_position[count]=i;
            count+=1;
            if(str[i]=='\0') break;
        }
        //test
        //   printf("%d\n",j);
    }
    for(int i=0;i+1<count;i++){
        rev_word(str,space_position[i],space_position[i+1]);
        //printf("rev for  %d\n",i);
    }
    printf("%s\n",str);    
}
