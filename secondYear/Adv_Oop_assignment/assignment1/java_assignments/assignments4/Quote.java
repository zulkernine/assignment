package java_assignments.assignments4;


public class Quote {
    private int id;
    private String quote;
    private String author;

    Quote(String q,String a,int id){
        quote = q;
        author = a ;
        this.id = id;
    }

    String getQuote(){ return quote; }
    String getAuthor(){ return author; }
    int getId(){ return id; }

    @Override
    public String toString() {
        return "\n\n"+quote + "\n-"+author+"\n";
    }
}
