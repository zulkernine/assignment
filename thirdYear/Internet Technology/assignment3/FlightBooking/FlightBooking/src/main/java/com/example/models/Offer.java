package com.example.models;

import org.bson.Document;
import org.bson.types.ObjectId;

import java.time.LocalDateTime;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Date;

public class Offer {
    private ObjectId id;
    public String source;
    public String destination;
    private String paymentOffer;
    private LocalDateTime validTill;
    private int price;

    public Offer() {
    }

    public Offer(Document doc) {
        this.id = (ObjectId) doc.get("_id");
        this.source = (String) doc.get("source");
        this.destination = (String) doc.get("destination");
        this.price = (Integer) doc.get("price");
        this.paymentOffer = (String) doc.get("paymentOffer");
        this.validTill = LocalDateTime.ofInstant(((Date) doc.get("validTill")).toInstant(), ZoneId.systemDefault());
    }

    public Offer(ObjectId id, String source, String destination, String paymentOffer, int price) {
        this.id = id;
        this.source = source;
        this.destination = destination;
        this.paymentOffer = paymentOffer;
        this.price = price;
    }

    public String getValidTill() {
        DateTimeFormatter myFormatObj = DateTimeFormatter.ofPattern("E, MMM dd yyyy");

        return validTill.format(myFormatObj);
    }

    public void setValidTill(LocalDateTime validTill) {
        this.validTill = validTill;
    }

    public ObjectId getId() {
        return id;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public String getPaymentOffer() {
        return paymentOffer;
    }

    public void setPaymentOffer(String paymentOffer) {
        this.paymentOffer = paymentOffer;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "Offer{" +
                "source='" + source + '\'' +
                ", destination='" + destination + '\'' +
                ", price=" + price +
                ", description=" + paymentOffer +
                '}';
    }

}



