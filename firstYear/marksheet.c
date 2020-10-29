#include<stdio.h>
int main(){
    
    struct {
        char name[30];
        char sub[][11] = {
        "Physics","Chemistry","Math","History","Geography"    
        };
        int marks[5];
    } students[5];
    for(int i=0;i<5;i++){
        printf("Enter the student's name:");
        scanf("%s",students[i].name);
        for(int j=0;j<5;j++){
            printf("Enter the number of %s =",students[i].sub[j]);
            scanf("%d",&students[i].marks[j]);
         }   
    }
    printf("Thank you");
    return 0;
}          
