package mocker.zulqarnain.listeners;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;

import javax.servlet.*;
import javax.servlet.annotation.*;

@WebListener
public class MongoContextListener implements ServletContextListener {

    public MongoContextListener() {
    }

    @Override
    public void contextInitialized(ServletContextEvent sce) {
        ServletContext ctx = sce.getServletContext();
        MongoClient mongo = MongoClients.create("mongodb://127.0.0.1:27017/?directConnection=true&serverSelectionTimeoutMS=2000&appName=mongosh+1.1.9");
        System.out.println("MongoClient initialized successfully");
        sce.getServletContext().setAttribute("MONGO_CLIENT", mongo);
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        MongoClient mongo = (MongoClient) sce.getServletContext()
                .getAttribute("MONGO_CLIENT");
        mongo.close();
        System.out.println("MongoClient closed successfully");
    }
}
