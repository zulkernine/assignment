package question2;

import java.util.List;

public class Question2 {
    public static void main(String[] args) {
        Vertex source = new Vertex(3, 3, true);
        Vertex destinaton = new Vertex(0, 0, false);
     
        GenerativeGraphWithBFS graph = new GenerativeGraphWithBFS(source);
        List<Vertex> path = graph.findPathByBFS(source, destinaton);
        System.out.println("Possible path: ");
        for(Vertex v : path){
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
