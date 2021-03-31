package java_assignments.assignments2;

import java.util.ArrayList;

public class ItemList {
    private ArrayList<Item> itemList;

    ItemList() {
        itemList = new ArrayList<Item>();
    }

    void addItem(String itemName,double rate,double quantity) throws IllegalArgumentException {
        for (Item it : itemList) {
            if (it.getName().toLowerCase().equals(itemName.toLowerCase())) {
                throw new IllegalArgumentException("Requested item already exist with item code: " + it.getItemCode());
            }
        }
        Item it = new Item(itemName, (float)rate, (float)quantity);
        itemList.add(it);
        System.out.println("New Item added, item code: " + it.getItemCode());
    }

    void updateRate(String itemCode, double rate) throws IllegalArgumentException {
        try {
            Item it = findItem(itemCode);
            if (rate > 0)
                it.setRate((float)rate);
            else
                throw new IllegalArgumentException("Item rate mut be greater than zero");
        } catch (ItemNotFoundException e) {
            System.out.println(e);
        }
    }

    void issueItem(String itemCode, float quantity) {
        try {
            Item item = findItem(itemCode);

            if (item.getQuantity() <= quantity) {
                System.out
                        .println("Enough quantity not available. available quantity:" + item.getQuantity() + " unit.");
            } else {
                item.setQuantity(item.getQuantity() - quantity);
                System.out.println("Item issued! Current quantity: " + item.getQuantity());
                System.out.println("Payment amount: "+ (item.getRate() * quantity));
            }

        } catch (ItemNotFoundException e) {
            System.out.println(e);
        }
    }

    void recievItem(String itemCode, float quantity) {
        try {
            Item item = findItem(itemCode);

            if (quantity <= 0) {
                System.out.println("Invalid quantity passed!");
            } else {
                item.setQuantity(item.getQuantity() + quantity);
                System.out.println("Item recieved! Current quantity: " + item.getQuantity());
            }

        } catch (ItemNotFoundException e) {
            System.out.println(e);
        }
    }

    public void displayItemDetails(String itemCode) {
        try {
            Item it = findItem(itemCode);
            System.out.println(it);
        } catch (ItemNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    public void displayItemsOverPrice(double price) {
        int count = 0;
        for (Item it : itemList) {
            if (it.getRate() >= price) {
                System.out.println(it);
                count++;
            }
        }
        if (count == 0)
            System.out.println("No Item found with given condition");
    }

    private Item findItem(String itemCode) throws ItemNotFoundException {
        for (Item it : itemList) {
            if (it.getItemCode().equals(itemCode))
                return it;
        }
        throw new ItemNotFoundException();
    }

    @Override
    public String toString() {
        String str="";
        for(Item it:itemList){
            str += it.toString() ;
            str+="\n\n";
        }

        return str;
    }
}
