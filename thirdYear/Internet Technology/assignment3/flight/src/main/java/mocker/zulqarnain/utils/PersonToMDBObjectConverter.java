package mocker.zulqarnain.utils;


import mocker.zulqarnain.models.Person;
import org.bson.Document;
import org.bson.types.ObjectId;

import com.mongodb.BasicDBObjectBuilder;
import com.mongodb.DBObject;

public class PersonToMDBObjectConverter {
    public static DBObject toDBObject(Person p) {
        BasicDBObjectBuilder builder = BasicDBObjectBuilder.start()
                .append("firstName", p.getFirstName())
                .append("lastName", p.getLastName())
                .append("age", p.getAge());
        if (p.getId() != null)
            builder = builder.append("_id", new ObjectId(p.getId()));
        return builder.get();
    }

    // convert DBObject Object to Person
    public static Person toPerson(Document doc) {
        Person p = new Person();
        p.setFirstName((String) doc.get("firstName"));
        p.setLastName((String) doc.get("lastName"));
        p.setAge(doc.getInteger("age"));
        ObjectId id = (ObjectId) doc.get("_id");
        p.setId(id.toString());
        return p;
    }
}
