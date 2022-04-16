import java.util.Collections;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

public class Question1 {

    static List<Integer> findPathByGreedyBFS(HashMap<Integer, List<DirectedEdge>> graph,int s,int d){
        HashMap<Integer, Integer> previousIntegerInPath = new HashMap<>();
        Hashtable<Integer, Boolean> visited = new Hashtable<>();

        previousIntegerInPath.put(s, null);
        PriorityQueue<DirectedEdge> pQueue = new PriorityQueue<DirectedEdge>();

        pQueue.add(new DirectedEdge(s, 0));

        while(!pQueue.isEmpty()){
            int v = pQueue.poll().rv;

            visited.put(v, true);

            for(DirectedEdge nvd : graph.get(v)){
                if(!visited.containsKey(nvd.rv)){
                    previousIntegerInPath.put(nvd.rv, v);
                    pQueue.add(nvd);

                    //destination found
                    if(nvd.rv==d){
                        return _makePath(previousIntegerInPath, d);
                    }
                }
            }
        }
        
        return List.of();
    }

    public static void main(String[] args) {
        HashMap<Integer, List<DirectedEdge>> _g = generateSampleGraph();
        List<Integer> path = findPathByGreedyBFS(_g, 1, 7);
        for(int i : path){
            System.out.println(i);
        }
        
    }

    static HashMap<Integer, List<DirectedEdge>> generateSampleGraph() {
        HashMap<Integer, List<DirectedEdge>> _g = new HashMap<Integer, List<DirectedEdge>>();
        _g.put(1, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(2, 5),
                new DirectedEdge(4, 3))));

        _g.put(2, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(3, 1))));

        _g.put(3, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(5, 6),
                new DirectedEdge(7, 8))));

        _g.put(4, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(5, 2),
                new DirectedEdge(6, 2))));

        _g.put(5, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(2, 4))));

        _g.put(6, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(7, 3))));

        _g.put(7, new LinkedList<DirectedEdge>(List.of(
                new DirectedEdge(5,4))));

        return _g;
    }

    static List<Integer> _makePath(HashMap<Integer, Integer> previousIntegerInPath, Integer dest) {
        List<Integer> path = new LinkedList<>();

        while (dest != null) {
            path.add(dest);
            dest = previousIntegerInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

}

class DirectedEdge implements Comparable {
    final int rv; // remote Integer or B for the edge A->B
    final int weight;

    DirectedEdge(int r, int w) {
        this.rv = r;
        this.weight = w;
    }

    @Override
    public int compareTo(Object o) {
        DirectedEdge d = (DirectedEdge)o;
        return  Integer.compare(weight, d.weight);
    }

    int getWeight(){ return weight; }
    int getRemoteInteger(){ return rv; }
}
