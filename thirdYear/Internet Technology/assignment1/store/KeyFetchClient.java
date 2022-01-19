package assignment1.store;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class KeyFetchClient {
    public static void main(String[] args) {
        try{
            if(args.length<1){
                System.out.println("Please provide port number (except 8000)");
                System.exit(1);
            }

            int port = Integer.parseInt(args[0]);
            // if(port == 8000){
            //     System.out.println("Please provide port number except 8000");
            //     System.exit(1);
            // }

            Socket server = new Socket("127.0.0.1",port);
            InputStream in = server.getInputStream();
            OutputStream out = server.getOutputStream();

            DataInputStream response = new DataInputStream(in);
            DataOutputStream request = new DataOutputStream(out);

            request.writeUTF("Connection request from guest");
            request.flush();

            System.out.println("Connected to server.");

            String initialMessage = response.readUTF();

            System.out.println(initialMessage);

            interactWithUser(server,response,request);

        }catch(Exception e){
            System.out.println(e);
        }
    }

    private static void interactWithUser(Socket sc,DataInputStream response, DataOutputStream request){
        Scanner scanner = new Scanner(System.in);

        while(sc.isConnected() && (!sc.isOutputShutdown() && !sc.isInputShutdown())){
            System.out.print("remote> ");
            String command = scanner.nextLine();
            try {
                request.writeUTF(command);
                request.flush();

                System.out.println(response.readUTF());
            } catch (Exception e) {
                System.out.println(e);
            }

            System.out.println();
        }

        scanner.close();
    }
}
