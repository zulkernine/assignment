/*
    Write a function to find the product of two numbers. 
    Call it number of times. Make the functions inline. 
    [check the time of execution and size of object code]
*/

#include<iostream>
using namespace std;

inline int product(int a,int b){
    return a*b;
}

int main(){
    //calling the function number of times
    for(int i=2;i<12;i++){
        int temp = product(i+1,2*i+1);
        cout<<"product "<<temp<<endl;
    }

    return 0;
}

/*
    Execution time using time command:
    real    0m0.006s
    user    0m0.005s
    sys     0m0.001s

    objectcode size: 17.1kb(clang++)
*/
