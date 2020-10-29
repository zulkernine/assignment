#include <stdio.h>
#include <time.h>

int main()
{
    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    int n;

    time(&timer);
    tm_info = localtime(&timer);
    
    printf("Enter the format no. to see the date.\n1. DD-MM-YY\n2. YY-MM-DD\n3. MM-DD-YY\nEnter the no.=");
    scanf("%d",&n);
    switch(n){
        case 1:{
            strftime(buffer, 26, "%d-%m-%Y ", tm_info);
            puts(buffer);
        };break;
        case 2:{
            strftime(buffer, 26, "%Y-%m-%d ", tm_info);
            puts(buffer);
        };break;
        case 3:{
            strftime(buffer, 26, "%m-%d-%Y ", tm_info);
            puts(buffer);
        };break;
    }

    //strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    //puts(buffer);

    return 0;
}
