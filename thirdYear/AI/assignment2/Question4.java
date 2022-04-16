import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Question4 {

    //Search only one level
    static void BFS(List<Boolean> visited,List<Integer> prev,Queue<Integer> q,HashMap<Integer, LinkedList<Integer>> graph){
        int s = q.size();
        for(int i=0;i<s;i++){
            int v = q.poll();
            visited.set(v, true);
            for(int adj : graph.get(v)){
                if(!visited.get(adj)){
                    q.add(adj);
                    prev.set(adj, v);
                }
            }
        }
    }

    static List<Integer> BidBS(HashMap<Integer, LinkedList<Integer>> graph,int source,int destination){
        ArrayList<Integer> prev_s = new ArrayList<>(List.of(Integer.MIN_VALUE));
        ArrayList<Integer> prev_d = new ArrayList<>(List.of(Integer.MIN_VALUE));
        ArrayList<Boolean> visited_s = new ArrayList<>(List.of(false));
        ArrayList<Boolean> visited_d = new ArrayList<>(List.of(false));
        for (int key : graph.keySet()) {
            visited_s.add(false);
            visited_d.add(false);
            prev_s.add(-1);
            prev_d.add(-1);
        }
        Queue<Integer> q_s = new LinkedList<>();
        Queue<Integer> q_d = new LinkedList<>();
        q_s.add(source);
        q_d.add(destination);

        while(!q_d.isEmpty() && !q_s.isEmpty()){
            BFS(visited_s, prev_s, q_s, graph);
            BFS(visited_d, prev_d, q_d, graph);

            int common = foundMatch(visited_d, visited_s);
            if(common!=-1){
                List<Integer> p1 = _makePath(prev_s, common);
                List<Integer> p2 = _makePath(prev_d, common);
                p2.remove(p2.size()-1);
                Collections.reverse(p2);

                p1.addAll(p2);

                return p1;
            }
        }

        return null;
    }

    static int foundMatch(ArrayList<Boolean> v1,ArrayList<Boolean> v2){
        for(int i=0;i<v1.size();i++){
            if(v1.get(i) && v2.get(i)) return i;
        }
        return -1;
    }



    static List<Integer> _makePath(List<Integer> previousIntegerInPath, Integer dest) {
        List<Integer> path = new LinkedList<>();

        while (dest != -1) {
            path.add(dest);
            dest = previousIntegerInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

    public static void main(String[] args) {
        HashMap<Integer, LinkedList<Integer>> _tree = _getSampleGraph();
        List<Integer> path = BidBS(_tree, 7, 10);
        for(int n:path) System.out.println(n);
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
