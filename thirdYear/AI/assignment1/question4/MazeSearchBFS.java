package question4;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

public class MazeSearchBFS {
    final ArrayList<ArrayList<Integer>> maze;

    MazeSearchBFS(ArrayList<ArrayList<Integer>> maze){
        this.maze = maze;
    }

    public static void main(String[] args) {
        ArrayList<ArrayList<Integer>> maze = new ArrayList<ArrayList<Integer>>();
        generateMaze(maze);

        MazeSearchBFS mazeSearch = new MazeSearchBFS(maze);
        List<Vertex> path = mazeSearch.findPathBFS(new Vertex(0,0), new Vertex(3,4));
        if(path == null){
            System.out.println("Path not found");
            return;
        }

        System.out.println("Shortest path length: " + (path.size()-1));
        System.out.println("Node order:");
        for(Vertex v : path){
            System.out.println(v);
        }
    }

    Vertex traverseEdge(Vertex source,Edges e){
        int i,j;
        i = source.first + e.first;
        j = source.second + e.second;

        if(i>=0 && i<maze.size() && j>=0 && j<maze.get(i).size() && maze.get(i).get(j)!=0){
            return new Vertex(i,j);
        }

        return null;
    }

    List<Edges> possibleEdges(){
        return List.of(
            new Edges(0, 1),
            new Edges(1, 0),
            new Edges(0, -1),
            new Edges(-1, 0)
        );
    }


    List<Vertex> findPathBFS(Vertex source,Vertex dest){
        HashMap<Vertex, Vertex> previousVertexInPath = new HashMap<>();
        Set<Vertex> visited = new HashSet<Vertex>();
        Queue<Vertex> vertices = new LinkedList<>();
        vertices.add(source);
        previousVertexInPath.put(source, null);

        do{
            Vertex v = vertices.poll();
            visited.add(v);

            for(Edges e : possibleEdges()){
                Vertex nv = traverseEdge(v, e);
                if(nv != null && !visited.contains(nv)){
                    previousVertexInPath.put(nv, v);
                    vertices.offer(nv);

                    if(nv.equals(dest)) return _makePath(previousVertexInPath, dest);
                }
            }

        }while(!vertices.isEmpty());

        return null;
    }

    List<Vertex> _makePath(HashMap<Vertex, Vertex> previousVertexInPath, Vertex dest) {
        List<Vertex> path = new LinkedList<>();

        while (dest != null) {
            path.add(dest);
            dest = previousVertexInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

    static void generateMaze(ArrayList<ArrayList<Integer>> maze){
        maze.add(new ArrayList<Integer>(List.of(1, 0, 1, 1, 1, 1, 0, 1, 1, 1)));
        maze.add(new ArrayList<Integer>(List.of(1, 0, 1, 0, 1, 1, 1, 0, 1, 1)));
        maze.add(new ArrayList<Integer>(List.of(1, 1, 1, 0, 1, 1, 0, 1, 0, 1)));
        maze.add(new ArrayList<Integer>(List.of(0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
        maze.add(new ArrayList<Integer>(List.of(1, 1, 1, 0, 1, 1, 1, 0, 1, 0)));
        maze.add(new ArrayList<Integer>(List.of(1, 0, 1, 1, 1, 1, 0, 1, 0, 0)));
        maze.add(new ArrayList<Integer>(List.of(1, 0, 0, 0, 0, 0, 0, 0, 0, 1)));
        maze.add(new ArrayList<Integer>(List.of(1, 0, 1, 1, 1, 1, 0, 1, 1, 1)));
        maze.add(new ArrayList<Integer>(List.of(1, 1, 0, 0, 0, 0, 1, 0, 0, 1)));
    }
}


