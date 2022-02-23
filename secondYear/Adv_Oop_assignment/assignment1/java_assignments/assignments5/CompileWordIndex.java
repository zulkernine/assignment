package java_assignments.assignments5;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class CompileWordIndex {
    public static void main(String[] args) {
        String fileName = "/home/zulfiqar/assignmentGit/secondYear/Adv_Oop_assignment/assignment1/java_assignments/assignments5/sample.txt";
        File file = new File(fileName);


        HashMap<String, ArrayList<String>> wordIndexes = new HashMap<String, ArrayList<String>>();

        try (Scanner scanner = new Scanner(file)) {
           int lineNumber = 1;
            while(scanner.hasNextLine()){
                String strList[] = scanner.nextLine().toLowerCase().split(" ");
                for(int i=0;i<strList.length;i++){
                    String key = strList[i];
                    if(wordIndexes.containsKey(key)){
                        wordIndexes.get(key).add("(" + lineNumber + "," + i + ")");
                    }else{
                        var list = new ArrayList<String>();
                        list.add("(" + lineNumber + "," + i + ")");
                        wordIndexes.put(key,list);
                    }
                }

                lineNumber++;
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println(e);
        }

        //Sort the key alphabetically
        ArrayList<String> sortedKey = new ArrayList<String>(wordIndexes.keySet());
        Collections.sort(sortedKey);

        System.out.println("\n(Line_number, word_number_in_that_line)");
        System.out.println("Words Indexes:\n");
        for(var key:sortedKey){
            System.out.println(key + " : " + wordIndexes.get(key));
        }

        // System.out.println(sortedKey);
    }

}
