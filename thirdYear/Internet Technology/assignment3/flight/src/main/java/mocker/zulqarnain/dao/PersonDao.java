package mocker.zulqarnain.dao;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import mocker.zulqarnain.models.Person;
import mocker.zulqarnain.utils.PersonToMDBObjectConverter;
import org.bson.Document;

import javax.servlet.ServletContext;
import java.util.ArrayList;
import java.util.List;

public class PersonDao {
    MongoCollection<Document> collection;

    public PersonDao(ServletContext context) {
        this.collection = ((MongoClient)context.getAttribute("MONGO_CLIENT")).getDatabase("patients").getCollection("records");
    }

    public List<Person> readAllPerson() {
        List<Person> data = new ArrayList<Person>();
        MongoCursor<Document> cursor = collection.find().cursor();
        while (cursor.hasNext()) {
            Document doc = cursor.next();
            Person p = PersonToMDBObjectConverter.toPerson(doc);
            data.add(p);
        }
        return data;
    }
}
