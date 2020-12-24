/*
    Design the class(es) for the following. Each account has account number and balance amount.
    A list of account is to be maintained where one can add and find account, display information
    of all accounts. While adding, account number must be unique. Withdraw object has account
    number (must exist) and amount (will not exceed balance amount of corresponding account).
    Withdraw object will update the balance of corresponding account in the list.
    Implement your design. Use friend function wherever required and again, modify your implementation
    to avoid friend function.
*/
#include<iostream>

class ACCOUNT{
    static int lastAccNO;
    const int accountNo;
    int balance;
public:
    // Iniitalise account No with next no of last number, and puts the value of balance(default to 0) 
    ACCOUNT(int balance = 0) :accountNo(++lastAccNO){}

    //Displays the account details
    friend std::ostream& operator<<(std::ostream& stream, const ACCOUNT acc);

    //Give access of private member to account list and withdraw object
    friend class ACCOUNT_LIST;
    friend class WITHDRAW;
};

int ACCOUNT::lastAccNO=100000;

class AccountNode{
    AccountNode* prev;
    AccountNode* next;
    ACCOUNT data;
public:
    AccountNode():prev(nullptr),next(nullptr){}

    friend class ACCOUNT_LIST;
    friend class WITHDRAW;
};

class ACCOUNT_LIST{
    AccountNode* head;//Ponter to the array of Accounts

    //Returns a ponter to the account for acccount number equals to accountNumber
    // if ite exists in the array,else null
    ACCOUNT* findAccount(int acountNumber);

public:
    //Initialise the accountList pointer to an array of ACCOUNT of length _size
    ACCOUNT_LIST();

    //Create a new account and ACCOUNT itself confirms the uniqueness of account number
    //Increaments the totalAccounts variable;
    int addAccount(int initialBalance = 0);

    //Displays accounts details of all acoounts, uses overloaded operator to do it
    void print();

    //Displays account details of Account corresponding to accNo
    void printAcc(int accNo);

    friend class WITHDRAW;

};

class WITHDRAW{
    int accountNumber;//account number
    int amount;//amount to be withdrawled
public:
    //Initialise pointer to the list , account number and balance
    //It also checks if required amount exist in the corresponding account else throw exception
    //It searches the account using private function ACCOUNT_LIST::findAccount, if it exists then
    // Executes the transaction and update the corresponding account in the available list pointed 
    //by parentList;
    WITHDRAW(ACCOUNT_LIST* parentList,int accNo, int amnt);
};
