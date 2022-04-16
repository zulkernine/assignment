package com.example.dao;

import com.example.models.Airport;
import com.example.models.Offer;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.model.Projections;
import org.bson.Document;
import static com.mongodb.client.model.Filters.*;

import javax.servlet.ServletContext;
import java.sql.Date;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class OfferDAO {
    MongoCollection<Document> offerCollection;
    MongoCollection<Document> airportCollection;

    public OfferDAO(ServletContext context) {
        this.offerCollection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("FlightData").getCollection("offers");
        this.airportCollection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("FlightData").getCollection("airports");
    }

    public List<Offer> readAllOffers() {
        List<Offer> data = new ArrayList<Offer>();
        MongoCursor<Document> cursor = offerCollection.find(gte("validTill", Date.valueOf(LocalDate.now()))).cursor();
        while (cursor.hasNext()) {
            Document doc = cursor.next();
            Offer p = new Offer(doc);
            String src = (String) Objects.requireNonNull(airportCollection.find(eq("airportCode", p.getSource())).projection(Projections.fields(
                    Projections.include("city"),
                    Projections.excludeId()
            )).first()).get("city");
            p.setSource(src);

            String dest = (String) Objects.requireNonNull(airportCollection.find(eq("airportCode", p.getDestination())).projection(Projections.fields(
                    Projections.include("city"),
                    Projections.excludeId()
            )).first()).get("city");
            p.setDestination(dest);
            data.add(p);
        }
        return data;
    }
}
