/*
    Write a function void f(int) that prints “inside f(int)”.
    Call the function with actual argument of type:
    i) int, ii) char, iii) float and iv) double.
    Add one more function f(float) that prints “inside f(float)”.
    Repeat the calls again and observe the outcomes.
*/

#include<iostream>
using namespace std;

void f(int n){
    cout << "inside f(int)" << endl;
}

void f(float f){
    cout << "inside f(float)" << endl;
}

int main(){
    int i = 10;
    char ch = 'c';
    float _f = 4.5;
    double d = 51.8;

    cout << "Calling using f(int)\n\n";
    f(i); f(ch); f(_f); f(d);

    cout << "Calling using f(float)\n\n";
    f(i); f(ch); f(_f); f(d);

    return 0;
}


/*
    assignment6.cpp: In function ‘int main()’:
    assignment6.cpp:28:28: error: call of overloaded ‘f(double&)’ is ambiguous
    28 |     f(i); f(ch); f(_f); f(d);
        |                            ^
    assignment6.cpp:12:6: note: candidate: ‘void f(int)’
    12 | void f(int n){
        |      ^
    assignment6.cpp:16:6: note: candidate: ‘void f(float)’
    16 | void f(float f){
        |      ^
    assignment6.cpp:31:28: error: call of overloaded ‘f(double&)’ is ambiguous
    31 |     f(i); f(ch); f(_f); f(d);
        |                            ^
    assignment6.cpp:12:6: note: candidate: ‘void f(int)’
    12 | void f(int n){
        |      ^
    assignment6.cpp:16:6: note: candidate: ‘void f(float)’
    16 | void f(float f){
        |
*/

