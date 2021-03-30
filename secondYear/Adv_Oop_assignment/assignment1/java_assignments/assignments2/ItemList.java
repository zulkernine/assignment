package java_assignments.assignments2;

import java.util.ArrayList;

public class ItemList {
    private ArrayList<Item> itemList;

    ItemList() {
        itemList = new ArrayList<Item>();
    }

    void addItem(String itemName) {
        for(Item it:itemList){
            if(it.getName().toLowerCase().equals(itemName.toLowerCase())){
                throw new IllegalArgumentException("Requested item already exist with item code: "+it.getItemCode());
            }
        }
        Item it = new Item(itemName,0,0);
        itemList.add(it);
        System.out.println("1 Item added, item code: "+it.getItemCode());
    }

    void updateRate(String itemCode, float rate) {
        Item it = findItem(itemCode);
        if(it!=null){
            if(rate>0)
                it.setRate(rate);
            else
                throw new IllegalArgumentException("Item rate mut be greater than zero");
        }else{
            
        }
    }

    void issueItem(String itemCode, float quantity) {
    }

    void recievItem(String itemCode, float quantity) {
    }

    void displayItemDetails(String itemCode) {
    }

    void displayItemsOverPrice(double price) {
    }

    private Item findItem(String itemCode){
        for(Item it:itemList){
            if(it.getItemCode().equals(itemCode)) return it;
        }
        
        return null;
    }

}
