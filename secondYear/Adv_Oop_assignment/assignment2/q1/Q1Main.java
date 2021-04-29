public class Q1Main {
    public static void main(String[] args) {
        BancAccount acc = new BancAccount("UYSAF67AS54347");
        
        acc.setBalance(2342.5);
        System.out.println("Balance: " + acc.getBalance() + "\tInterest: "+acc.getInterest(4));
        BancAccount.setInterestRate(4.5);
        System.out.println("Balance: " + acc.getBalance() + "\tInterest: " + acc.getInterest(4));
        System.out.println("Interest Rate: " + BancAccount.getInterestRate());

        System.out.println(acc);
    }
}


