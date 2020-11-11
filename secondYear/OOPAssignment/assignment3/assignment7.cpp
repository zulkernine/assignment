/*
    Define functions f(int, int) and f (char, int).
    Call the functions with arguments of type (int, char), (char,char) and (float, float).
*/

#include<iostream>

using namespace std;

void f(int a,int b){
    cout<<"Inside f(int,int) = "<<a<<" "<<b<<endl;
}

void f(char c, int b){
    cout << "Inside f(char,int) = " << c << " " << b << endl;
}

int main(){

    cout<<"Calling with(int,char):(12,'v'):-\n";
    f(12,'v');

    cout << "Calling with(char,char):('s','(')):-\n";
    f('s','(');

    cout << "Calling with(float,float):(12.432,42.541):-\n";
    f(12.432,42.541);
}


/*
    Program not compiled for amibiguous function call of f(12.432,42.541);
*/

