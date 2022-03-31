package com.example.models;

import org.bson.Document;

public class Journey {
    String src;
    String dest;
    String departureTime;
    String arrivalTime;
    String day;
    Integer fare;
    String airlineName;

    public Journey(){}

    public Journey(Document doc){
        src = (String) doc.get("src");
        dest = (String) doc.get("dest");
        departureTime = (String) doc.get("departureTime");
        arrivalTime = (String) doc.get("arrivalTime");
        day = (String) doc.get("day");
        fare = (Integer) doc.get("fare");
        airlineName = (String) doc.get("airlineName");
    }

    public String getSrc() {
        return src;
    }

    public void setSrc(String src) {
        this.src = src;
    }

    public String getDest() {
        return dest;
    }

    public void setDest(String dest) {
        this.dest = dest;
    }

    public String getDepartureTime() {
        return departureTime;
    }

    public void setDepartureTime(String departureTime) {
        this.departureTime = departureTime;
    }

    public String getAirlineName() {
        return airlineName;
    }

    public void setAirlineName(String airlineName) {
        this.airlineName = airlineName;
    }

    public String getArrivalTime() {
        return arrivalTime;
    }

    public void setArrivalTime(String arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public String getDay() {
        return day;
    }

    public void setDay(String day) {
        this.day = day;
    }

    public Integer getFare() {
        return fare;
    }

    public void setFare(Integer fare) {
        this.fare = fare;
    }

    @Override
    public String toString() {
        return "Journey{" +
                "source='" + src + '\'' +
                ", destination='" + dest + '\'' +
                ", Airline=" + airlineName +
                ", price=" + fare +
                '}';
    }
}
