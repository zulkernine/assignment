/*
    Write a function max (a, b) that will return the reference of larger value.
    Store the returned information to x where x is a
    i) variable of type a or b,
    ii) variable referring to type of a or b.
    In both the cases modify x. Check also the values of a and b.
*/

#include<iostream>
using namespace std;

int& max(int& num1, int& num2){
    return num1 > num2 ? num1 : num2;
}

int main(){
    int a=23,b=62;

    int x_int = max(a,b);
    cout<<"Max of a="<<a<<" b="<<b<<" is x="<<x_int<<endl;
    x_int = 43;
    cout << "After modifying x(same type of a/b), values of a=" << a << " b=" << b << endl;

    int &x_ref = max(a,b);
    cout << "Max of a=" << a << " b=" << b << " is x=" << x_ref << endl;
    x_ref = 43;
    cout << "After modifying x(ref type), values of a=" << a << " b=" << b << endl;

    return 0;
}

