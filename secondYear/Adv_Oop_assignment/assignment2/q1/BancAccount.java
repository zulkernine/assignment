public class BancAccount {
    private String accno;
    private double balance;
    private static double interestRate;

    BancAccount(String no){
        accno = no;
        balance = 0;
    }

    static{
        interestRate = 10;
    }

    String getAccno(){ return accno; }
    double getBalance() { return balance; }
    double getInterest (double year){
        return (balance*year*interestRate*0.01);
    }
    static double getInterestRate(){ return interestRate; }

    void setBalance(double bal){
        if(bal>0)
            balance = bal;
        else
            System.out.println("Invaid Balance: Balance must positive value");
    }
    static void setInterestRate(double rate){
        if (rate > 0)
            interestRate = rate;
        else
            System.out.println("Invaid Rate: Rate must positive value");
    }

    @Override
    public String toString() {
        return "Acc No: "+accno+"\tBalance: "+balance;
    }

}
