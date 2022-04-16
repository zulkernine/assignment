package q3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Q3 {

    HashMap<Grid,Boolean> visited;
    HashMap<Grid,Grid> previous;
    Grid fG;

    Q3(){
        visited = new HashMap<>();
        previous = new HashMap<>();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Print the current state and put 0 instead of gap:");
        ArrayList<ArrayList<Integer>> state = new ArrayList<ArrayList<Integer>>();

        for(int i=0;i<3;i++){
            state.add(new ArrayList<Integer>());
            for(int j=0;j<3;j++){
                int t = scanner.nextInt();
                state.get(i).add(t);
            }
        }

        Grid grid = new Grid(state);
        Q3 q3 = new Q3();
        q3.previous.put(grid, null);
        if(q3.DLS(grid, 43)){
            System.out.println("Path found:");
            List<Grid> path = _makePath(q3.previous, q3.fG);
            System.out.println("Number of steps: "+path.size());
            for(Grid g:path){
                System.out.println(g);
            }
        }else{
            System.out.println("Path not found");
        }

        scanner.close();
    }

    static List<Grid> _makePath(HashMap<Grid, Grid> previousIntegerInPath, Grid dest) {
        List<Grid> path = new LinkedList<>();

        while (dest != null) {
            path.add(dest);
            dest = previousIntegerInPath.get(dest);
        }

        Collections.reverse(path);
        return path;
    }

    boolean DLS(Grid grid,int limit){
        if(grid.isFinalState()){
            fG = grid;
            return true;
        }
        if(limit<=0) return false;

        visited.put(grid, true);
        var adjs = grid.adjuscentNodes();

        for(Grid g : adjs){
            if(!visited.containsKey(g)){
                previous.put(g, grid);

                if(DLS(g,limit-1)) return true;
            }
        }

        return false;
    }
}
