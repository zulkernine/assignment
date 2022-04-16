package question3;

import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class GenerativeDepthFirstSearch {
    final int capacity1,capacity2,dest;

    HashMap<Vertex, List<Vertex>> graph = new HashMap<>();
    HashMap<Vertex, Vertex> previousVertexInPath = new HashMap<>();

    GenerativeDepthFirstSearch(int c1,int c2,int d) {
        capacity1 = c1;
        capacity2 = c2;
        dest = d;

        Vertex root = new Vertex(c1,c2);
        graph.put(root, new LinkedList<>());
        previousVertexInPath.put(root, null); // root node has no parent.
    }

    List<Edges> generatePossiblEdges(int f,int s){
        List<Edges> edges = new LinkedList<>(List.of(
            new Edges(0,capacity2),
            new Edges(0,-capacity2),
            new Edges(capacity1,0),
            new Edges(-capacity1,0)
        ));

        if((capacity1-f)>s){
            edges.add(new Edges(+s, -s));
        }else{
            int t = capacity1-f;
            if(t!=0)
            edges.add(new Edges(+t, -t));
        }

        if ((capacity2 - s) > f) {
            edges.add(new Edges(-f, +f));
        } else {
            int t = capacity2-s;
            if (t != 0)
            edges.add(new Edges(-t, +t));
        }

        return edges;
    }

    public List<Vertex> findPathByBFS() {
        Vertex source = new Vertex(capacity1,capacity2);
        Vertex d1 = new Vertex(capacity1, capacity2,0,dest);
        Vertex d2 = new Vertex(capacity1, capacity2,dest,0);

        HashMap<Vertex, Boolean> visited = new HashMap<>();
        for (Vertex key : graph.keySet()) {
            visited.put(key, false);
        }
        Stack<Vertex> vertices = new Stack<>();
        // Add first element
        vertices.add(source);

        do {
            Vertex v = vertices.pop();

            if (visited.get(v) == null || !visited.get(v)) {
                visited.put(v, true);
            }

            // Go to adjascent nodes and add to quese if valid and not visited
            for (Edges e : generatePossiblEdges(v.first, v.second)) {
                Vertex nv = v.traverseEdge(e);

                // avoid invalid states.
                if (nv != null && !visited.containsKey(nv)) {
                    vertices.push(nv);
                    previousVertexInPath.put(nv, v);

                    if (nv.equals(d1)) {
                        return _makePath(previousVertexInPath, d1);
                    }else if(nv.equals(d2)){
                        return _makePath(previousVertexInPath, d2);
                    }
                }
            }

        } while (!vertices.isEmpty());

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

}
