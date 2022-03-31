package com.example.dao;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.example.models.Airport;
import org.bson.Document;

import javax.servlet.ServletContext;
import java.util.ArrayList;
import java.util.List;

public class AirportDAO {
    MongoCollection<Document> collection;

    public AirportDAO(ServletContext context) {
        this.collection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("FlightData").getCollection("airports");
    }

    public List<Airport> readAllAirports() {
        List<Airport> data = new ArrayList<Airport>();
        MongoCursor<Document> cursor = collection.find().cursor();
        while (cursor.hasNext()) {
            Document doc = cursor.next();
            Airport p = new Airport(doc);
            data.add(p);
        }
        return data;
    }
}
