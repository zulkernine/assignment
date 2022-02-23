package assignment1.store;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

class ServerHandler implements Runnable {
    static ArrayList<String> managerAuths;
    static {
        managerAuths = new ArrayList<String>();
        managerAuths.addAll(Arrays.asList(
                "abcd1234",
                "pqrs789",
                "jkl456",
                "wxyz876"));
    }

    Socket client;
    HashMap<String, String> myStorage;
    HashMap<Integer, HashMap<String, String>> globalStorage;
    boolean isManager;

    public ServerHandler(Socket c, HashMap<Integer, HashMap<String, String>> storage) {
        client = c;
        isManager = false;
        globalStorage = storage;

        if (!globalStorage.containsKey(c.getPort())) {
            globalStorage.put(c.getPort(), new HashMap<String, String>());
        }

        myStorage = globalStorage.get(c.getPort());
    }

    @Override
    public void run() {
        try {
            InputStream in = client.getInputStream();
            OutputStream out = client.getOutputStream();

            DataInputStream request = new DataInputStream(in);
            DataOutputStream response = new DataOutputStream(out);

            boolean shouldContinue = false;

            System.out.println(request.readUTF());

            response.writeUTF("Connected to server, avialable commands: GET,PUT,MANAGER,OTHERS,VIEW,EXIT");
            response.flush();

            do {
                shouldContinue = executeComand(request.readUTF(), response);
                response.flush();
            } while (shouldContinue);

            response.writeUTF("Exiting... ");
            response.flush();

            client.close();

            System.out.println("Exiting server handler thread");
        } catch (Exception e) {
            System.out.println(e);
        }

    }

    boolean executeComand(String arg, DataOutputStream resp)throws IOException {
        String args[] = arg.split(" ");

        switch (args[0]) {
            case Command.GET: {
                if (args.length < 2)
                    resp.writeUTF("Please provide key\n Format: GET key_name");
                else
                    resp.writeUTF(myStorage.getOrDefault(args[1], "NOT FOUND"));

            }
                break;

            case Command.PUT: {
                if (args.length < 2) {
                    resp.writeUTF("Please provide key\n Format: GET key_name");
                } else if (args.length < 3) {
                    resp.writeUTF("Please provide new value for the key\nFormat: PUT key_name value");
                } else {
                    myStorage.put(args[1], args[2]);
                    resp.writeUTF("Value updated");
                }
            }
                break;

            case Command.MANAGER: {
                if (args.length < 2) {
                    resp.writeUTF("Please provide password\n Format: MANAGER password\n");
                } else {
                    if (managerAuths.contains(args[1])) {
                        resp.writeUTF("Successfully authorised!");
                        isManager = true;
                    } else {
                        resp.writeUTF("Password didn't match. Please contact admin and update your password.\n");
                    }
                }
            }
                break;

            case Command.OTHERS: {
                if (!isManager) {
                    resp.writeUTF(
                            "You are not authorized to view others' storage,use MANAGE command to upgrade role.\n");
                } else {
                    resp.writeUTF("Currently stored user id: \n" + globalStorage.keySet().toString());
                }

            }
                break;

            case Command.VIEW: {
                if (!isManager) {
                    resp.writeUTF(
                            "You are not authorized to view others' storage,use MANAGE command to upgrade role.\n");
                } else {
                    if (args.length < 2) {
                        resp.writeUTF("Please provide user-id\n Format: VIEW user_ID\n");
                    } else if (!globalStorage.containsKey(Integer.parseInt(args[1]))) {
                        resp.writeUTF("USER not found :(");
                    } else {
                        resp.writeUTF("Storage of user - " + args[1] + "\n"
                                + (globalStorage.get(Integer.parseInt(args[1])).toString()));
                    }
                }
            }
                break;

            case Command.EXIT:
                return false;

            default: {
                resp.writeUTF("COMMAND NOT FOUND");
            }
        }

        return true;
    }

}
