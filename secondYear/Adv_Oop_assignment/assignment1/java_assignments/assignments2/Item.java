package java_assignments.assignments2;

public class Item {
    private String itemCode;
    private String itemName;
    private float rate;
    private float quantity;

    private static int itemOrder;

    static{
        itemOrder = 0;
    }

    Item(){}
    Item(String name,float rate,float quantity){
        this.itemName = new String(name);
        this.rate = rate;
        this.quantity = quantity;
        ++Item.itemOrder;

        this.itemCode = name.substring(0, 3) + String.format("%03d", Item.itemOrder);
    }

    public void setRate(float r){
        if(r>0){
            this.rate = r;
        }else{
            throw new IllegalArgumentException("Rate must be greater than 0");
        }
    }
    public float getRate(){ return rate; }

    public void setQuantity(float q){
        if (q >= 0) {
            this.quantity = q;
        } else {
            throw new IllegalArgumentException("Quality must be greater than or equals to 0");
        }
    }
    public float getQuantity(){ return quantity; }

    public String getName(){ return itemName; }
    public String getItemCode(){ return itemCode; }

    @Override
    public String toString() {
        return ("Code: "+itemCode+" \tName: "+itemName+" \tQuantity: "+quantity+" \tRate: "+rate) ;
    }
    @Override
    public boolean equals(Object obj) {
        if(obj==this) return true;
        if(!(obj instanceof Item)) return false;
        
        Item it = (Item)obj;
        return this.itemCode.equals(it.itemCode);
    }

}
