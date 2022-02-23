/*
    Write a function swap (a, b) to interchange the values of two variables. Do not use pointers.
*/

#include<iostream>
using namespace std;

void swap(int& num1, int& num2){
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

int main(){
    int a = 12, b = 52;
    cout << "Before swaping: a=" << a << " b=" << b << endl;
    swap(a,b);
    cout << "After swaping: a=" << a << " b=" << b << endl;

}
