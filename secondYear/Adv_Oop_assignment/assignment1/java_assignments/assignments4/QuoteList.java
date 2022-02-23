package java_assignments.assignments4;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class QuoteList {
    ArrayList<Quote> list;

    QuoteList(){
        list = new ArrayList<Quote>();
    }

    // public void writeList(String fileName){
    //     ObjectOutputStream oos = null;
    //     FileOutputStream fout = null;
    //     try {
    //         fout = new FileOutputStream("G:\\address.ser", true);
    //         oos = new ObjectOutputStream(fout);
    //         oos.writeObject(list);
    //     } catch (Exception ex) {
    //         ex.printStackTrace();
    //     } finally {
    //         if (oos != null) {
    //             try{
    //                 oos.close();
    //             }catch(IOException e){
    //                 System.out.println(e);
    //             }
    //         }
    //     }
    // }


    public void readList(File quoteFile){
        Scanner sc=null;
        try {
            int len=0;
            sc = new Scanner(quoteFile);
            len = sc.nextInt();
            for(int i=0;i<len;i++){
                String q, a;
                int id = sc.nextInt();
                sc.nextLine();//Clear the '\n' charecter after the int from buffer
                q = sc.nextLine(); 
                a = sc.nextLine(); 
                list.add(new Quote(q, a, id));
            }
        } catch (FileNotFoundException e) {
            System.out.println(e);
            return;
        }

        if(sc!=null) sc.close();
    }

    Quote getQuote(int id){
        if(id >= list.size()) return list.get(0);

        return list.get(id);
    }
}
