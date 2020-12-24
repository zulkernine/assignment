/*
    Design a BALANCE class with account number, balance and date of last update.
    Consider a TRANSACTION class with account number, date of transaction, amount
    and transaction type (W for withdrawal and D for deposit). If it is a withdrawal
    check whether the amount is available or not. Transaction object will make necessary
    update in the BALANCE class.
*/

#include<iostream>
#include<ctime>

using namespace std;

class BALANCE{
    const int acount_number;
    double amount; //Total amount/balance available
    long long last_update_time; //Stores last UTC time of update as a string

public:
    /* Following constructor takes arguements i) acc_no: unique new account number,
    ii)Stores the creation time as last update time
    iii)And takes initial deposit amount default to zero*/
    BALANCE(int acc_no, int deposit_amnt = 0) :acount_number(acc_no), amount(deposit_amnt){
        last_update_time = time(nullptr);
    }

    inline int getAccountNumber() const{ return this->acount_number; }

    friend ostream& operator<<(ostream& stream, const BALANCE& balance);
    friend class TRANSACTION; //Gives access of private data to transaction class.
};

// BALANCE::BALANCE(int acc_no, int deposit_amnt = 0) :acount_number(acc_no), amount(deposit_amnt){
//     last_update_time = time(nullptr);
// }

ostream& operator<<(ostream& stream, const BALANCE& balance){
    stream << "Account Number: " << balance.acount_number << "\n";
    stream << "Current Balance: " << balance.amount << "\n";
    time_t temp = balance.last_update_time;
    stream << "Last Update Time: " << asctime(localtime(&temp)) << "\n";
    return stream;
}

class TRANSACTION{
    const int account_number;
    long long transaction_time;
    const char type;// withdrawl(w) or deposit(d)
    double amount;//Amount of transaction
public:
    /* It saves account no,and transaction type */
    TRANSACTION(int acc_no, char trns_type);

    inline void setAmount(int m){ if (m > 0) amount = m; }
    bool execute(BALANCE& bl);// It makes change in corresponding BALANCE class, 
    //consequently stores current time in transaction_time

    friend ostream& operator<<(ostream& stream, const TRANSACTION& transaction);
};

TRANSACTION::TRANSACTION(int acc_no, char trns_type) :account_number(acc_no), type(trns_type){}

bool TRANSACTION::execute(BALANCE& bl){
    if (account_number == bl.acount_number){
        if ((type == 'w') && (amount < bl.amount)){
            bl.amount -= amount;
        }
        else if ((type == 'd') && (amount > 0)){
            bl.amount += amount;
        }
        transaction_time = time(nullptr);
        return true;
    }
    return false;
}

ostream& operator<<(ostream& stream, const TRANSACTION& transaction){
    stream << "Transaction Details:\n";
    stream << "Acc No: " << transaction.account_number << "\n";
    stream << "Type: " << (transaction.type == 'd' ? "Deposit" : "Withdrawl") << "\n";
    stream << "Amount: " << transaction.amount << "\n";
    time_t temp = transaction.transaction_time;
    stream << asctime(localtime(&temp)) << "\n";

    return stream;
}



//Testing Code

int main(){
    static int AccountNumberOffset = 1000000;

    BALANCE balance(AccountNumberOffset++);
    while (true){
        cout << "1.Depoit 2.Withdrawl 3.See Balance 4.Exit\nOption: ";
        int opt;
        cin >> opt;
        switch (opt){
        case 1:{
            TRANSACTION t(balance.getAccountNumber(), 'd');
            cout << "Deposit amount: ";
            double amt;cin >> amt;
            t.setAmount(amt);

            t.execute(balance);
            cout << t << endl;
        }
              break;
        case 2:{
            cout << "Withdrawl amount: ";
            double amt;cin >> amt;
            TRANSACTION t(balance.getAccountNumber(), 'w');
            t.setAmount(amt);

            t.execute(balance);
            cout << t << endl;
        }
              break;
        case 3: cout << balance << endl;
            break;
        case 4: exit(0);
        default:{
            cout << "Please enter a valid option.\n";
        }

        }
    }
}
