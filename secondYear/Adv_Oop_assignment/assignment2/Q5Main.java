import java.util.ArrayList;
import java.util.Scanner;

public class Q5Main {
    private static double creditLimit;
    private static double priviledgedCreditLimit;
    static {
        creditLimit = 200000;
        priviledgedCreditLimit = 500000;
    }

    public static void main(String[] args) {
        ArrayList<Customer> customers = new ArrayList<Customer>();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            printOptions();
            int opt = Integer.parseInt(scanner.nextLine());
            System.out.println("\n\n");
            switch (opt) {
            case 0: {
                scanner.close();
                return;
            }

            case 1: {
                String name, number;
                boolean status;
                System.out.print("Name: ");
                name = scanner.nextLine();
                System.out.print("Phone Number: ");
                number = scanner.nextLine();
                System.out.print("Priviledged Account(true/false): ");
                status = Boolean.parseBoolean(scanner.nextLine());

                Customer cus = new Customer(name, number, status);
                customers.add(cus);
                System.out.println("New acount created, account number: " + cus.getId());
            }
                break;

            case 2: {
                String id;
                System.out.print("Account number: ");
                id = scanner.nextLine();
                Customer cus = findCustomer(id, customers);
                if (cus == null) {
                    System.out.println("No customer exist with id: " + id);
                } else {
                    double userCredit = cus.getPriviledgedStatus() ? priviledgedCreditLimit : creditLimit;
                    double userLoan;
                    System.out.print("Apply loan amount: ");
                    userLoan = Double.parseDouble(scanner.nextLine());
                    if ((userLoan + cus.getCurrentLoan()) <= userCredit) {
                        System.out.println("Your loan is sanctioned!");
                        cus.setCurrentLoan(cus.getCurrentLoan() + userLoan);
                        System.out.println("Your loan is disbursed now.");
                    } else {
                        System.out.println("You can apply upto " + Double.toString(userCredit - cus.getCurrentLoan())
                                + ". Repay current loan or upgrade status to apply for more.");
                    }
                }
            }
                break;

            case 3: {
                String id;
                System.out.print("Account number: ");
                id = scanner.nextLine();
                Customer cus = findCustomer(id, customers);
                if (cus == null) {
                    System.out.println("No customer exist with given id!");
                    break;
                }

                double userCredit = cus.getPriviledgedStatus() ? priviledgedCreditLimit : creditLimit;

                System.out.println(cus);
                System.out.println("Your total credit limit: " + Double.toString(userCredit));
                System.out.println("You can still apply upto: " + Double.toString(userCredit - cus.getCurrentLoan()));
            }
                break;

            case 4: {
                String data;
                boolean bool;
                String id;
                System.out.print("Account number: ");
                id = scanner.nextLine();
                Customer cus = findCustomer(id, customers);
                if (cus == null) {
                    System.out.println("No customer exist with given id!");
                    break;
                }

                System.out.print("Update name?(true/false): ");
                bool = Boolean.parseBoolean(scanner.nextLine());
                if (bool) {
                    System.out.print("New Name: ");
                    data = scanner.nextLine();
                    cus.setName(data);
                }

                System.out.print("Update phone number?(true/false): ");
                bool = Boolean.parseBoolean(scanner.nextLine());
                if (bool) {
                    System.out.print("New number: ");
                    data = scanner.nextLine();
                    cus.setPhoneNumber(data);
                }

            }
                break;

            case 5: {
                String id;
                System.out.print("Account number: ");
                id = scanner.nextLine();
                Customer cus = findCustomer(id, customers);
                if (cus == null) {
                    System.out.println("No customer exist with given id!");
                    break;
                }

                System.out.println(cus);

            }
                break;

            case 6: {
                for (var cus : customers) {
                    System.out.println(cus + "\n\n");
                }
            }
                break;

            case 7: {
                String id;
                System.out.print("Account number: ");
                id = scanner.nextLine();
                Customer cus = findCustomer(id, customers);
                if (cus == null) {
                    System.out.println("No customer exist with given id!");
                    break;
                }

                double amt;
                System.out.print("Payment amount: ");
                amt = Double.parseDouble(scanner.nextLine());

                if (amt >= cus.getCurrentLoan()) {
                    amt -= cus.getCurrentLoan();
                    cus.setCurrentLoan(0);
                    System.out.println("Your loan is repayed. Disbarsed amount: " + Double.toString(amt));
                } else {
                    cus.setCurrentLoan(cus.getCurrentLoan() - amt);
                    System.out.println("Your current loan amount: " + Double.toString(cus.getCurrentLoan()));
                }
            }
                break;
            default: {
                System.out.println("Option must be within 0-7, both inclusive.");
            }

            }
        }

    }

    static void printOptions() {
        System.out.print("\n\n0.Exit\n" + "1.New Account\n" + "2.Apply For Loan\n"
                + "3.Check current loan or credit limit\n" + "4.Update Account Details\n" + "5.View Account Details\n"
                + "6.Display all accounts\n" + "7.Pay loan\n" + "Option:- ");
    }

    static Customer findCustomer(String id, ArrayList<Customer> customers) {
        for (Customer c : customers) {
            if (c.getId().equals(id))
                return c;
        }
        return null;
    }
}

class Customer {
    private final String id;
    private String name;
    private double currentLoan;
    private boolean isPriviledged;
    private String phoneNumber;

    Customer(String name, String number, boolean isPriviledged) {
        currentLoan = 0;
        this.name = name;
        phoneNumber = number;
        this.isPriviledged = isPriviledged;

        this.id = Long.toString(System.currentTimeMillis());
    }

    Customer() {
        currentLoan = 0;
        isPriviledged = false;
        this.id = Long.toString(System.currentTimeMillis());
    }

    String getId() {
        return id;
    }

    String getName() {
        return name;
    }

    String getPhoneNumber() {
        return phoneNumber;
    }

    double getCurrentLoan() {
        return currentLoan;
    }

    boolean getPriviledgedStatus() {
        return isPriviledged;
    }

    void setName(String name) {
        this.name = name;
    }

    void setPhoneNumber(String num) {
        this.phoneNumber = num;
    }

    void setCurrentLoan(double amount) {
        if (amount < 0) {
            System.out.println("Invalid amount: Amount must be positive value!");
        } else {
            currentLoan = amount;
        }
    }

    void setPriviledgedStatus(boolean status) {
        this.isPriviledged = status;
    }

    @Override
    public String toString() {
        String str = "Customer ID: " + id + "\tName: " + name + "\nPhone Number: " + phoneNumber + "\t Priviledged: "
                + Boolean.toString(isPriviledged) + "\n" + "Current Loan Amount: " + Double.toString(currentLoan);

        return str;
    }

}
