package java_assignments.assignments4;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

public class User {
    private String name;
    // private int history[]; // Save last 5 quotes
    // private int counter;
    private int lastQuoteId;

    User(String n) {
        name = n;
        // counter = 0;
        // history = new int[5];

        File file = new File(
                "/home/zulfiqar/assignmentGit/secondYear/Adv_Oop_assignment/assignment1/java_assignments/assignments4/"
                        + name + "_quote_history.txt");
        if (file.exists()) {
            try (Scanner sc = new Scanner(file)) {
                name = sc.nextLine();
                lastQuoteId = sc.nextInt();
                // for(int i=0;i<5;i++){
                // history[i] = sc.nextInt();

                // if(history[i] == -1 && counter == 0) counter = i;
                // }

            } catch (FileNotFoundException e) {
                System.out.println(e);
            } catch (Exception e) {
                System.out.println(e);
            }
        }
        // else {
        // for (int i = 0; i < 5; i++)
        // history[i] = -1;
        // }
    }

    // boolean searchId(int id) {
    // for (int i = 0; i < history.length; i++) {
    // if (id == history[i])
    // return true;
    // else if (history[i] == -1)
    // break;
    // }
    // return false;
    // }

    void addQuote(int id) {
        // if (counter >= 5)
        // counter = (counter % 5);

        // history[counter] = id;
        // counter++;
        lastQuoteId = id;
    }

    void save() {
        PrintWriter writer = null;
        try {
            writer = new PrintWriter(
                    "/home/zulfiqar/assignmentGit/secondYear/Adv_Oop_assignment/assignment1/java_assignments/assignments4/"
                            + name + "_quote_history.txt",
                    "UTF-8");
            writer.println(name);
            writer.println(lastQuoteId);

            // for (int h : history)
            // writer.println(h);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        if (writer != null)
            writer.close();
    }

    int getLastQuoteId() {
        // if(counter == 0) return history[4];
        // else{
        // return history[counter-1];
        // }

        return lastQuoteId;
    }
}
