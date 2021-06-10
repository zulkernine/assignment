from time import time_ns,asctime,localtime,time

class BankAccount:
    def __init__(self,name,balance):
        self.__balance = balance
        self.__accHolderName = name
        self.__accountNumber = time_ns()

    def deposit(self,amount):
        if amount>0 :
            self.__balance += amount
            print(
                f"DEPOSIT: ₹{amount} deposited. Current balance: ₹{self.__balance}")
        else :
            print("ERROR: Deposit amount must be positive!")

    def withdraw(self,amount):
        if amount>0 :
            if self.__balance > amount :
                self.__balance -= amount
                print(
                    f"WITHDRAWL: ₹{amount} withdrawled. Current balance: ₹{self.__balance}")
            else :
                print(
                    f"WITHDRAWL: Enough balance not available. Current balance: ₹{self.__balance}")
        else :
            print("ERROR: withdrawl amount must be positive")

    def get_balance(self):
        return self.__balance

    def change_pin(self,new_pin):
        if isinstance(new_pin, int):
            self.__accountNumber = new_pin
        else:
            print("ERROR: PIN must be an integer.")

    def get_pin(self):
        return self.__accountNumber

class SavingsAccount(BankAccount):
    def __init__(self, name, balance,interest_rate):
        super().__init__(name, balance)
        self.__interest_rate = interest_rate

    def updateBalanceWithInterest(self,year):
        interest = self._BankAccount__balance * self.__interest_rate * 0.01 * year
        self._BankAccount__balance += interest
        print(
            f"INTEREST: ₹{interest} credited. Current balance: ₹{self._BankAccount__balance}")

def main() :
    name = input("Name: ")
    balance = float(input("First deposit: "))
    rate = float(input("Interest rate: "))
    sv_acc = SavingsAccount(name, balance, rate)
    deposit_amnt = float(input("Deposit amount: "))
    sv_acc.deposit(deposit_amnt)
    withdraw_amnt = float(input("Withdrawl amount: "))
    sv_acc.withdraw(withdraw_amnt)
    sv_acc.updateBalanceWithInterest(5.5)
    print("Current new balance: ₹{0}, Acc-No: {1}".format(sv_acc.get_balance(),sv_acc.get_pin()))
    

if __name__ == "__main__" :
    main()

