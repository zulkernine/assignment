package java_assignments.assignments2;

import java.util.Scanner;

public class TestingItem {
    public static void main(String[] args) {
        ItemList itemList = new ItemList();
        if(!isRoot())
            System.out.println("\n\nRun this program as root(sudo) to avail SEO mode. Current Mode: Shopkeeper");
        else
            System.out.println("\n\nRunning in SEO mode");

        Scanner scanner = new Scanner(System.in);

        while(true){
            printOption();
            switch(scanner.nextInt()){
                case 1:{
                    String name;
                    double rate,quantity;

                    clearInputBuffer(scanner); 
                    System.out.print("Item name: ");
                    name = scanner.nextLine();

                    System.out.print("Item rate: ");
                    rate = scanner.nextDouble();

                    System.out.print("Item Quantity: ");
                    quantity = scanner.nextDouble();

                    try{
                        itemList.addItem(name.trim(),rate,quantity);
                    }catch(IllegalArgumentException e){
                        System.out.println(e.getMessage());
                    }catch(Exception e){
                        System.out.println(e);
                    }

                }
                break;

                case 2:{
                    String itemCode;
                    double rate;

                    System.out.print("Item Code: ");
                    clearInputBuffer(scanner);
                    itemCode = scanner.nextLine().trim();

                    System.out.print("New rate of the Item: ");
                    rate = scanner.nextDouble();

                    try{
                        itemList.updateRate(itemCode, rate);
                    }catch(IllegalArgumentException e){
                        System.out.println(e.getMessage());
                    }
                    catch(Exception e){
                        System.out.println(e);
                    }
                }
                break;

                case 3:{
                    String itemCode;float quantity;

                    clearInputBuffer(scanner);
                    System.out.print("Item Code: ");
                    itemCode = scanner.nextLine().trim();

                    System.out.print("Required quantity: ");
                    quantity = scanner.nextFloat();

                    itemList.issueItem(itemCode, quantity);
                }
                break;

                case 4:{
                    String itemCode;
                    float quantity;

                    clearInputBuffer(scanner);
                    System.out.print("Item Code: ");
                    itemCode = scanner.nextLine().trim();

                    System.out.print("Required quantity: ");
                    quantity = scanner.nextFloat();

                    itemList.recievItem(itemCode, quantity);
                }
                break;

                case 5:{
                    String itemCode;
                    clearInputBuffer(scanner);
                    System.out.print("Item Code: ");
                    itemCode = scanner.nextLine().trim();

                    itemList.displayItemDetails(itemCode);
                }
                break;

                case 6:{
                    System.out.println(itemList);
                }
                break;

                case 7:{
                    double price;
                    System.out.print("Item price: ");
                    price = scanner.nextDouble();

                    itemList.displayItemsOverPrice(price);
                }
                break;

                case 8:{
                    scanner.close();
                    return;
                }
                
                default:{
                    System.out.println("Enter a valid option between 1-8 both inclusive");
                }
            }
        }
    }

    private static void printOption() {
        System.out.println("\n\n\nChoose Option:-\n");
        if (isRoot()) {
            System.out.println(
                "1.Add Item \n" + 
                "2.Update Item Rate \n"
            );
        }
        System.out.println(
            "3.Issue Item \n" + 
            "4.Recieve Item \n" + 
            "5.Display an Item \n" + 
            "6.Display all Item \n" + 
            "7.Display all Item over certain amount \n" + 
            "8.Exit \n"
        );
        System.out.print("Option:- ");
    }

    private static boolean isRoot() {
        return System.getProperty("user.name").equals("root");
    }
    
    private static void clearInputBuffer(Scanner scanner) {

        if (scanner.hasNextLine())
            scanner.nextLine();
    }
}
