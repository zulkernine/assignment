package assignment1.question2;

public class Question2 {
    public static void main(String[] args) {
        Vertex source = new Vertex(3, 3, true);
        Vertex destinaton = new Vertex(0, 0, false);

        GenerativeGraphWithBFS graph = new GenerativeGraphWithBFS(source);
        for(Vertex v : graph.findPathByBFS(source, destinaton)){
            System.out.println(v);
        }
    }
}

/**
 * Vertex(int m,int c,bool b)
 * Edge(int m,int c,bool b)
 * possible edges: (1,0),(2,0),(1,1),(0,2) with b true or false,
 * 
 * 
 * 
*/
