package com.zulqarnain.cma.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.PersistenceConstructor;
import org.springframework.data.mongodb.core.index.TextIndexed;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.Field;
import java.util.ArrayList;

@Document(collection = "clothings")
public class Cloth {
    @Id
    private String id;
    @Field(name = "SKU")
    private String sku;

    @TextIndexed
    private String name;

    @TextIndexed
    private String shortDescription;
    @TextIndexed
    private String description;
    private int price;
    private int discount;

    public int getReviews() {
        return reviews;
    }

    public void setReviews(int reviews) {
        this.reviews = reviews;
    }

    private int reviews;
    private double rating;

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    @TextIndexed
    private ArrayList<String> categories;
    private ArrayList<String> images;

    public int getDiscount() {
        return discount;
    }

    public void setDiscount(int discount) {
        this.discount = discount;
    }

    public ArrayList<String> getAvailableSize() {
        return availableSize;
    }

    public void setAvailableSize(ArrayList<String> availableSize) {
        this.availableSize = availableSize;
    }

    private ArrayList<String> availableSize;
    private ArrayList<String> color;

    public Cloth() {
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
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


    public ArrayList<String> getColor() {
        return color;
    }

    public void setColor(ArrayList<String> color) {
        this.color = color;
    }

    @PersistenceConstructor
    public Cloth(String sku, String name, String shortDescription, String description, int price, ArrayList<String> categories, ArrayList<String> images, ArrayList<String> availableSize, ArrayList<String> color) {
        this.sku = sku;
        this.name = name;
        this.shortDescription = shortDescription;
        this.description = description;
        this.price = price;
        this.categories = categories;
        this.images = images;
        this.availableSize = availableSize;
        this.color = color;
    }
}
