package question3;

import java.util.List;

public class Question3 {
    public static void main(String[] args) {
        GenerativeDepthFirstSearch graph = new GenerativeDepthFirstSearch(3,5,4);
        List<Vertex> path = graph.findPathByBFS();
        if(path==null){
            System.out.println("Path not found!");
        }else{
            System.out.println("Possible path: ");
            for (Vertex v : path) {
                System.out.println(v);
            }
        }
    }
}
