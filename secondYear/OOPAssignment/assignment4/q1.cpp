/*
    Design the class(es) for the following. Each account has account number and balance amount.
    A list of account is to be maintained where one can add and find account, display information
    of all accounts. While adding, account number must be unique. Withdraw object has account
    number (must exist) and amount (will not exceed balance amount of corresponding account).
    Withdraw object will update the balance of corresponding account in the list.
    Implement your design. Use friend function wherever required and again, modify your implementation
    to avoid friend function.
*/

class ACCOUNT{
    static int lastAccNO;
    const int accountNo;
    int balance;
    public:
    // Iniitalise account No with next no of last number, and puts the value of balance(default to 0) 
    ACCOUNT(int balance=0):accountNo(++lastAccNO){}

    //Give access of private member to account list and withdraw object
    friend class ACCOUNT_LIST;
    friend class WITHDRAW;
};

class ACCOUNT_LIST{
    ACCOUNT* accountList;
    const int size;

    //Returns a ponter to the account for acccount number equals to accountNumber
    // if ite exists in the array,else null
    ACCOUNT* findAccount(int acountNumber);

    public:
    //Initialise the accountList pointer to an array of ACCOUNT of length _size
    ACCOUNT_LIST(int _size):size(_size){}

    //Create a new account and ACCOUNT itself confirms the uniqueness of account number
    int addAccount(int initialBalance=0);

    friend class WITHDRAW;

};

class WITHDRAW{
    const ACCOUNT_LIST *parentList;//Points to the account_list object
    int accountNumber;//account number
    int amount;//amount to be withdrawled
public:
    //Initialise pointer to the list , account number and balance
    //It also checks if required amount exist in the corresponding account else throw exception
    //It searches the account using private function ACCOUNT_LIST::findAccount
    WITHDRAW(ACCOUNT_LIST* parent,int accNo,int amnt):parentList(parent){}

    // Executes the transaction and update the corresponding account in the available list pointed 
    //by parentList;
    void execute();
};

