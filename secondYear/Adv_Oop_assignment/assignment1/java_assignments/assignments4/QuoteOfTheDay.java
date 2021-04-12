package java_assignments.assignments4;

import java.io.File;

public class QuoteOfTheDay {
    public static void main(String[] args) {
        String quoteFile = "./java_assignments/assignments4/Quote_List.txt";
        File file = new File(quoteFile);
        if(!file.exists()){
            System.out.println("Quote list,doesn't exist!");
            return;
        }

        QuoteList quoteList = new QuoteList();
        quoteList.readList(file);

        String userName = System.getProperty("user.name");
        User user = new User(userName);

        int lastQuoteId = user.getLastQuoteId()+1;
        Quote q = quoteList.getQuote(lastQuoteId);
        user.addQuote(q.getId());
        user.save();

        System.out.println(q);

        return;

    }
}
