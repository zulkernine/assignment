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
using namespace std;

class ACCOUNT{
    static int lastAccNO;
    const int accountNo;
    double balance;
public:
    // Iniitalise account No with next no of last number, and puts the value of balance(default to 0) 
    ACCOUNT(double balance = 0) :accountNo(++lastAccNO), balance(balance){}

    //Displays the account details
    friend std::ostream& operator<<(std::ostream& stream, const ACCOUNT& acc);

    //Give access of private member to account list and withdraw object
    friend class ACCOUNT_LIST;
    friend class WITHDRAW;
};

std::ostream& operator<<(std::ostream& stream, const ACCOUNT& acc){
    stream << "Account Number: " << acc.accountNo << "\n";
    stream << "Current Balance: " << acc.balance << "\n";

    return stream;
}

int ACCOUNT::lastAccNO = 100000;

class AccountNode{
    AccountNode* prev;
    AccountNode* next;
    ACCOUNT data;
public:
    AccountNode(ACCOUNT _data) :prev(nullptr), next(nullptr), data(_data){}

    friend class ACCOUNT_LIST;
    friend class WITHDRAW;
};

class ACCOUNT_LIST{
    AccountNode* head;//Ponter to the array of Accounts

    //Returns a ponter to the account for acccount number equals to accountNumber
    // if ite exists in the array,else null
    AccountNode* findAccount(int acountNumber);

public:
    //Initialise the accountList pointer to an array of ACCOUNT of length _size
    ACCOUNT_LIST() :head(nullptr){};

    //Create a new account and ACCOUNT itself confirms the uniqueness of account number
    //Increaments the totalAccounts variable;
    int addAccount(double initialBalance);

    void depositAmount(int accNo, double amount);

    //Displays accounts details of all acoounts, uses overloaded operator to do it
    void print();

    friend class WITHDRAW;

};

AccountNode* ACCOUNT_LIST::findAccount(int accountNumber){
    AccountNode* cur = head;
    while (cur){
        if (cur->data.accountNo == accountNumber) break;
        cur = cur->next;
    }
    return cur;
}

int ACCOUNT_LIST::addAccount(double initialBalance = 0){
    ACCOUNT acc(initialBalance);
    AccountNode* node = new AccountNode(acc);

    if (head){
        node->next = head;
        head->prev = node;
    }

    head = node;
    return acc.accountNo;
}

void ACCOUNT_LIST::depositAmount(int accNo, double amount){
    AccountNode* node = findAccount(accNo);
    if (node && amount > 0){
        node->data.balance += amount;
    }
    else{
        cout << "Invalid Details\n";
    }
}

void ACCOUNT_LIST::print(){
    AccountNode* cur = head;

    cout << "\n";
    while (cur){
        cout << cur->data;
        cout << "\n";

        cur = cur->next;
    }
}


class WITHDRAW{
    const int accountNumber;//account number
    const int amount;//amount to be withdrawled
public:
    //Initialise pointer to the list , account number and balance
    //It also checks if required amount exist in the corresponding account else throw exception
    //It searches the account using private function ACCOUNT_LIST::findAccount, if it exists then
    // Executes the transaction and update the corresponding account in the available list pointed 
    //by parentList;
    WITHDRAW(ACCOUNT_LIST& parentList, int accNo, int amnt) :accountNumber(accNo), amount(amnt){
        AccountNode* node = parentList.findAccount(accNo);

        if (node){
            if (node->data.balance >= amount){
                node->data.balance -= amount;
            }
            else{
                throw(string("Not Sufficient Balance Available"));
            }
        }
        else{
            throw string("Invalid Account Number");
        }
    };

    friend ostream& operator<<(ostream& stream, const WITHDRAW& w){
        stream << "Withdrawl:\n";
        stream << "Amount: " << w.amount << "\n";
        stream << "Account Number: " << w.accountNumber << "\n";

        return stream;
    }
};

class WithdrawlList{
    class Node{
    public:
        Node* next;
        const WITHDRAW data;
        Node(WITHDRAW data) :data(data), next(nullptr){}
    };

    Node* head;

public:
    WithdrawlList() :head(nullptr){}

    void addWithdrawl(WITHDRAW w);
    void print();
};
void WithdrawlList::addWithdrawl(WITHDRAW w){
    Node* node = new Node(w);

    if (head){
        node->next = head;
    }
    head = node;
}
void WithdrawlList::print(){
    Node* cur = head;
    while (cur){
        cout << cur->data << "\n";
        cur = cur->next;
    }
}


int main(){
    ACCOUNT_LIST accList;
    WithdrawlList wList;

    while (true){
        cout << "Choose an option:\n1.Create New Account\n2.Withdrawl Amount\n";
        cout << "3.Show all Account\n4.Show All Withdrawls\n5.Deposit\n6.Exit\nOption: ";

        int opt;cin >> opt;
        switch (opt){
        case 1:{
            double d;
            cout << "Initial Deposit Amount:";cin >> d;
            if (d < 0) cout << "Amount must be greater than equals to 0\n";
            else{
                int accNo = accList.addAccount(d);
                cout << "Your Account Number: " << accNo << "\n";
            }
        }
              break;

        case 2:{
            int accNo;double amount;
            cout << "Withdrawl Amount: ";cin >> amount;
            cout << "Account NUmber: ";cin >> accNo;

            try{
                WITHDRAW w(accList, accNo, amount);
                wList.addWithdrawl(w);
            }
            catch (string e){
                cout << e << endl;
            }
        }
              break;

        case 3:{
            cout << "All Accounts:\n";
            accList.print();
            cout << "\n";
        }
              break;

        case 4:{
            cout << "All Widrawls:\n";
            wList.print();
            cout << "\n";
        }
              break;

        case 5:{
            int accNo;double amount;
            cout << "Deosit Amount: ";cin >> amount;
            cout << "Account NUmber: ";cin >> accNo;
            accList.depositAmount(accNo, amount);
        }
              break;
        case 6:exit(0);

        default:
            cout << "Enter a valid option\n";
        }
    }
}
