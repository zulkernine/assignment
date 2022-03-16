package assignment1.question2;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.TreeMap;

public class GenerativeGraphWithBFS {
    HashMap<Vertex,List<Vertex>> graph = new HashMap<>();
    TreeMap<Vertex,Vertex> previousVertexInPath = new TreeMap<>();

    GenerativeGraphWithBFS(Vertex root){
        graph.put(root, new LinkedList<>());
        previousVertexInPath.put(root, null); //root node has no parent.
    }

    // In this cases, number of missionary on the boat is always greater than
    // cannibals
    // or there are no missionary on the boat.
    final static List<EdgeWeight> possibleWeights = new LinkedList<>(List.of(
            new EdgeWeight(1, 0, true),
            new EdgeWeight(1, 0, false),
            new EdgeWeight(2, 0, true),
            new EdgeWeight(2, 0, false),
            new EdgeWeight(0, 1, true),
            new EdgeWeight(0, 1, false),
            new EdgeWeight(1, 1, true),
            new EdgeWeight(1, 1, false),
            new EdgeWeight(0, 2, false),
            new EdgeWeight(0, 2, true)));

    public List<Vertex> findPathByBFS(Vertex source,Vertex dest){
        HashMap<Vertex,Boolean> visited = new HashMap<>();
        for(Vertex key : graph.keySet()){
            visited.put(key, false);
        }
        Queue<Vertex> vertices = new LinkedList<>();
        List<Vertex> path = new LinkedList<>();
        //Add first element
        vertices.add(source);

        do{

            Vertex v = vertices.poll();
            if(visited.get(v)==null || !visited.get(v)){
                // if(v.canibals>v.misonary) continue;
                visited.put(v, true);
            }

            // Go to adjascent nodes and add to quese if valid and not visited
            for(EdgeWeight e : possibleWeights){
                Vertex nv = v.traverseEdge(e);
                // avoid invalid states.
                if(nv.isValid() && !visited.containsKey(nv)){
                    previousVertexInPath.put(nv, v);

                    if(v == dest){
                        return _makePath(previousVertexInPath, dest);
                    }
                    vertices.offer(nv);
                }
            }
            
        }while(!vertices.isEmpty());

        return List.of();
    }

    List<Vertex> _makePath(TreeMap<Vertex,Vertex> previousVertexInPath,Vertex dest){
        List<Vertex> path = new LinkedList<>();

        while(dest != null){
            path.add(dest);
            dest = previousVertexInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

}
