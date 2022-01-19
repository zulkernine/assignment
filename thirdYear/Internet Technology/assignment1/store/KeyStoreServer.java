package assignment1.store;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;


public class KeyStoreServer{
    static HashMap<Integer,HashMap<String,String>> storage;

    static{
        // storage = (HashMap<Integer, HashMap<String, String>>)Collections.synchronizedMap(new HashMap<Integer, HashMap<String, String>>());
        storage = new HashMap<Integer, HashMap<String, String>>();
    }

    public static void main(String[] args) {
        try {
            ServerSocket _server = new ServerSocket(8000);
            System.out.println("started server at port: 8000");

            while(true){
                Socket client = _server.accept();
                System.out.printf("Accepted connection from:%d\n",client.getPort());

                ServerHandler _handler = new ServerHandler(client,storage);
                Thread _t = new Thread(_handler);
                _t.start();
            }
        
        } catch (IOException e) {
            System.out.println(e);
        } catch (Exception e){
            System.out.println(e);
        }
    }

}



