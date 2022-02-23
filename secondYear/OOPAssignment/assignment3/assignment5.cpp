/*
    Write a function that will have income and tax rate as arguments and will return tax amount.
    In case tax rate is not provided it will be automatically taken as 10%. Call it with and without tax rate.
*/

#include<iostream>
using namespace std;

double tax(double amount, double rate = 10){
    double tax_amount;
    tax_amount = (amount * rate) / 100.0;
    return tax_amount;
}

int main(){
    double amount, rate;
    cout << "Enter amount: ";
    cin >> amount;

    double tax_amount = tax(amount);
    cout << "Default tax value: " << tax_amount << endl;

    cout << "Enter rate: ";cin >> rate;
    tax_amount = tax(amount, rate);

    cout << "New tax amount: " << tax_amount << endl;

    return 0;
}

