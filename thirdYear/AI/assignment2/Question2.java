import java.util.Collections;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

public class Question2 {

    HashMap<Character, List<Character>> graph;
    HashMap<Character, Character> previousIntegerInPath;

    Question2(HashMap<Character, List<Character>> g){
        this.graph = g;
        previousIntegerInPath = new HashMap<>();
    }

    boolean DLS(char source,char dest,int limit){
        System.out.print(source + "  ");
        if(source == dest) return true;

        if(limit<=0) return false;

        for(char ch : graph.get(source)){
            if(DLS(ch,dest,limit-1)){
                return true;
            }
        }
        return false;
    }

    boolean IDDLS(char source,char dest,int max_depth){
        for(int i=0;i<max_depth;i++){
            if(DLS(source,dest,i)){
                return true;
            }
            System.out.println();
        }
        return false;
    }

    
    public static void main(String[] args) {
        HashMap<Character, List<Character>> _g = generateSampleGraph();
        Question2 q2 = new Question2(_g);

        if(q2.IDDLS('A', 'N', 4)){
            System.out.println();
            System.out.println("Target reached within max depth");
        }else{
            System.out.println();
            System.err.println("Target isnot reachable within max depth");
        }

    }

    static HashMap<Character, List<Character>> generateSampleGraph() {
        HashMap<Character, List<Character>> _g = new HashMap<Character, List<Character>>();
        _g.put('A', new LinkedList<>(List.of('B','C')));
        _g.put('B', new LinkedList<>(List.of('A','D','E')));
        _g.put('C', new LinkedList<>(List.of('A','F','G','H')));
        _g.put('D', new LinkedList<>(List.of('B','I','J')));
        _g.put('E', new LinkedList<>(List.of('B','K','L','M')));
        _g.put('F', new LinkedList<>(List.of('N', 'C')));
        _g.put('G', new LinkedList<>(List.of('C')));
        _g.put('H', new LinkedList<>(List.of('O','P', 'C')));
        _g.put('I', new LinkedList<>(List.of('D')));
        _g.put('J', new LinkedList<>(List.of('D')));
        _g.put('K', new LinkedList<>(List.of('E')));
        _g.put('L', new LinkedList<>(List.of('E')));
        _g.put('M', new LinkedList<>(List.of('E')));
        _g.put('N', new LinkedList<>(List.of('F')));
        _g.put('O', new LinkedList<>(List.of('H')));
        _g.put('P', new LinkedList<>(List.of('H')));
        return _g;
    }

    static List<Character> _makePath(HashMap<Character, Character> previousIntegerInPath, Character dest) {
        List<Character> path = new LinkedList<>();

        while (dest != null) {
            path.add(dest);
            dest = previousIntegerInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

}
