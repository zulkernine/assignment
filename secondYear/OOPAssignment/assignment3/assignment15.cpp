/*
    Design a BALANCE class with account number, balance and date of last update.
    Consider a TRANSACTION class with account number, date of transaction, amount
    and transaction type (W for withdrawal and D for deposit). If it is a withdrawal
    check whether the amount is available or not. Transaction object will make necessary
    update in the BALANCE class.
*/

class BALANCE{
    int annount_number;
    double amount; //Total amount/balance available
    char last_update_time[30]; //Stores last UTC time of update as a string

public:
    /* Following constructor takes arguements i) acc_no: unique new account number, 
    ii)Stores the creation time as last update time 
    iii)And takes initial deposit amount default to zero*/
    BALANCE(int acc_no,int deposit_amnt=0);

    friend class TRANSACTION; //Gives access of private data to transaction class.

};

class TRANSACTION{
    int account_number;
    char transaction_time[30];
    char type;// withdrawl(w) or deposit(d)
public:
    /* It saves account no,and transaction type */
    TRANSACTION(int acc_no,char trns_type);
    
    void execute();// It makes change in corresponding BALANCE class, 
    //consequently stores current time in transaction_time



};


