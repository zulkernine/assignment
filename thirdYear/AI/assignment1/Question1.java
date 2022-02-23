package assignment1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Question1 {

    public static LinkedList<Integer> findPathFromGraph(HashMap<Integer, LinkedList<Integer>> graph, int src, int dst) {
        LinkedList<Integer> path = new LinkedList<>();

        // Create and initialize distance and visited array.
        ArrayList<Integer> distance = new ArrayList<>(List.of(Integer.MIN_VALUE));
        ArrayList<Integer> pred = new ArrayList<>(List.of(Integer.MIN_VALUE));
        ArrayList<Boolean> visited = new ArrayList<>(List.of(false));
        for (int key : graph.keySet()) {
            if (key == src)
                distance.add(0);
            else
                distance.add(Integer.MAX_VALUE);

            visited.add(false);
            pred.add(-1);
        }
        Queue<Integer> q = new LinkedList<>();
        q.add(src);
        boolean found = false;
        

        //BFS
        while(!(q.isEmpty()) && !found){
            int curKey = q.poll();
            
            for(int adjk : graph.get(curKey)){
                if(!visited.get(adjk)){
                    // mark current not visited
                    visited.set(curKey, true);

                    q.add(adjk);
                    distance.set(adjk, (distance.get(curKey)+1));
                    pred.set(adjk, curKey);
                    if(adjk == dst){
                        found = true;
                        break;
                    }
                }
            }
        }

        if(!found){
            return null;
        }

        System.out.println("Shortest distance: "+distance.get(dst));

        while(dst != -1){
            path.addFirst(dst);
            dst = pred.get(dst);
        }

        return path;
    }

    public static void main(String args[]) {
        HashMap<Integer, LinkedList<Integer>> _graph = _getSampleGraph();

        // System.out.println(_graph.get(1));
        
        LinkedList<Integer> path = findPathFromGraph(_graph, 5, 7);
        System.out.println("Found path: " + path);
    }

    private static HashMap<Integer, LinkedList<Integer>> _getSampleGraph() {
        HashMap<Integer, LinkedList<Integer>> _graph = new HashMap<>();
        _graph.put(1, new LinkedList<Integer>(List.of(8, 5, 2)));
        _graph.put(2, new LinkedList<Integer>(List.of(1, 9)));
        _graph.put(3, new LinkedList<Integer>(List.of(8)));
        _graph.put(4, new LinkedList<Integer>(List.of(8)));
        _graph.put(5, new LinkedList<Integer>(List.of(1)));
        _graph.put(6, new LinkedList<Integer>(List.of(8, 7, 10)));
        _graph.put(7, new LinkedList<Integer>(List.of(6)));
        _graph.put(8, new LinkedList<Integer>(List.of(1, 3, 4, 6)));
        _graph.put(9, new LinkedList<Integer>(List.of(2)));
        _graph.put(10, new LinkedList<Integer>(List.of(6)));

        return _graph;
    }
}
