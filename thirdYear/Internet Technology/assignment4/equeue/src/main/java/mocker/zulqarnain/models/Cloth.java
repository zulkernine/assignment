package mocker.zulqarnain.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.PersistenceConstructor;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.Field;
import java.util.ArrayList;

@Document(collection = "clothings")
public class Cloth {
    @Id
    private String id;
    @Field(name = "SKU")
    private String sku;
    private String name;
    private String shortDescription;
    private String description;
    private int price;
    private ArrayList<String> categories;
    private ArrayList<String> images;
    private ArrayList<String> size;
    private ArrayList<String> color;

    public Cloth() {
    }

    public String getSku() {
        return sku;
    }

    public void setSku(String sku) {
        this.sku = sku;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getShortDescription() {
        return shortDescription;
    }

    public void setShortDescription(String shortDescription) {
        this.shortDescription = shortDescription;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public ArrayList<String> getCategories() {
        return categories;
    }

    public void setCategories(ArrayList<String> categories) {
        this.categories = categories;
    }

    public ArrayList<String> getImages() {
        return images;
    }

    public void setImages(ArrayList<String> images) {
        this.images = images;
    }

    public ArrayList<String> getSize() {
        return size;
    }

    public void setSize(ArrayList<String> size) {
        this.size = size;
    }

    public ArrayList<String> getColor() {
        return color;
    }

    public void setColor(ArrayList<String> color) {
        this.color = color;
    }

    @PersistenceConstructor
    public Cloth(String sku, String name, String shortDescription, String description, int price, ArrayList<String> categories, ArrayList<String> images, ArrayList<String> size, ArrayList<String> color) {
        this.sku = sku;
        this.name = name;
        this.shortDescription = shortDescription;
        this.description = description;
        this.price = price;
        this.categories = categories;
        this.images = images;
        this.size = size;
        this.color = color;
    }
}
