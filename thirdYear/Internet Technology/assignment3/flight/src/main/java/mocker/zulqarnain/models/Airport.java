package mocker.zulqarnain.models;

import org.bson.Document;

public class Airport {
    private String id;
    private String name;
    private String city;
    private String country;
    private String airportCode;
    private String region;

    public Airport() {
    }

    public Airport(Document doc) {
        this.id = (String) doc.get("_id");
        this.name = (String) doc.get("name");
        this.city = (String) doc.get("city");
        this.country = (String) doc.get("country");
        this.airportCode = (String) doc.get("airportCode");
        this.region = (String) doc.get("region");
    }

    public Airport(String id, String name, String city, String country, String airportCode, String region) {
        this.id = id;
        this.name = name;
        this.city = city;
        this.country = country;
        this.airportCode = airportCode;
        this.region = region;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getAirportCode() {
        return airportCode;
    }

    public void setAirportCode(String airportCode) {
        this.airportCode = airportCode;
    }

    public String getRegion() {
        return region;
    }

    public void setRegion(String region) {
        this.region = region;
    }


}
