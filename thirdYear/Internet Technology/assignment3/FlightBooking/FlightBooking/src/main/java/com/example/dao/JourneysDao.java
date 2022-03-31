package com.example.dao;

import com.example.models.Journey;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import org.bson.Document;

import javax.servlet.ServletContext;
import java.util.ArrayList;
import java.util.List;

import static com.mongodb.client.model.Filters.and;
import static com.mongodb.client.model.Filters.eq;

public class JourneysDao {
    MongoCollection<Document> airportCollection;
    MongoCollection<Document> journeysCollection;

    public JourneysDao(ServletContext context) {
        this.airportCollection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("FlightData").getCollection("airports");
        this.journeysCollection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("FlightData").getCollection("Journeys");
    }

//    public List<Offer> readAllOffers() {
//        List<Offer> data = new ArrayList<Offer>();
//        MongoCursor<Document> cursor = offerCollection.find().cursor();
//        while (cursor.hasNext()) {
//            Document doc = cursor.next();
//            Offer p = new Offer(doc);
//            String src = (String) Objects.requireNonNull(airportCollection.find(eq("airportCode", p.getSource())).projection(Projections.fields(
//                    Projections.include("city"),
//                    Projections.excludeId()
//            )).first()).get("city");
//            p.setSource(src);
//
//            String dest = (String) Objects.requireNonNull(airportCollection.find(eq("airportCode", p.getDestination())).projection(Projections.fields(
//                    Projections.include("city"),
//                    Projections.excludeId()
//            )).first()).get("city");
//            p.setDestination(dest);
//            data.add(p);
//        }
//        return data;
//    }

    public List<Journey> getAvailableJourneys(String sourceAirport, String destinationAirport, String day){
        List<Journey> data = new ArrayList<Journey>();
        MongoCursor<Document> cursor = journeysCollection.find(and(eq("src",sourceAirport),eq("dest",destinationAirport),eq("day",day))).cursor();
        while(cursor.hasNext()){
            data.add(new Journey(cursor.next()));
        }

        return  data;
    }
}
