package q3;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Grid{
    ArrayList<ArrayList<Integer>> state;
    final static int SIZE = 3;

    Grid(ArrayList<ArrayList<Integer>> g){
        this.state = new ArrayList<ArrayList<Integer>>();
        for(ArrayList<Integer> l : g){
            var lc = new ArrayList<Integer>();
            for(int i : l){
                lc.add(i);
            }
            state.add(lc);
        }
    }

    private ArrayList<Integer> currentGapPosition(){
        for(int i=0;i<state.size();i++){
            for(int j=0;j<state.get(i).size();j++){
                if(state.get(i).get(j)==0){
                    return new ArrayList<Integer>(List.of(i,j));
                }
            }
        }
        return null;
    }

    final static ArrayList<ArrayList<Integer>> probableMoves(){
        return new ArrayList<>(List.of(
            new ArrayList<>(List.of(0,1)),
            new ArrayList<>(List.of(1,0)),
            new ArrayList<>(List.of(0,-1)),
            new ArrayList<>(List.of(-1,0))
        ));
    }

    final static ArrayList<ArrayList<Integer>> getValidPosition(ArrayList<Integer> currentPos){
        int i = currentPos.get(0);
        int j = currentPos.get(1);

        ArrayList<ArrayList<Integer>> vp = new ArrayList<ArrayList<Integer>>();

        for(ArrayList<Integer> l : probableMoves()){
            int m = i+l.get(0),n=j+l.get(1);
            if(m<SIZE && m>=0 && n<SIZE && n>=0){
                vp.add( new ArrayList<>(List.of(m,n)));
            }
        }

        return vp;
    }

    ArrayList<Grid> adjuscentNodes(){
        ArrayList<Integer> gap = currentGapPosition();
        ArrayList<ArrayList<Integer>> validMoves = getValidPosition(gap);
        ArrayList<Grid> grids = new ArrayList<Grid>();

        for(ArrayList<Integer> l:validMoves){
            Grid g = new Grid(state);
            g.swap(gap, l);
            grids.add(g);
        }

        return grids;
    }

    void swap(ArrayList<Integer> i,ArrayList<Integer> j){
        int temp = state.get(i.get(0)).get(i.get(1));
        state.get(i.get(0)).set(i.get(1), state.get(j.get(0)).get(j.get(1)));
        state.get(j.get(0)).set(j.get(1),temp);
    }

    @Override
    public String toString() {
        String str="";

        for(ArrayList<Integer> l : state){
            for(int i : l){
                str += (Integer.toString(i) + " ");
            }
            str += "\n";
        }

        return str;
    }

    /*
     * Expected final state:
     * 0 1 2
     * 3 4 5
     * 6 7 8
     */
    boolean isFinalState(){
        int k = 0;
        for(int i=0;i<state.size();i++){
            for(int j=0;j<state.get(i).size();j++,k++){
                if(k!=state.get(i).get(j)) return false;
            }
        }
        return true;
    }

    private int getSingleLineValue(){
        int k=0;
        for(int i=0;i<state.size();i++){
            for(int j=0;j<state.get(i).size();j++){
                k = (k*10 + state.get(i).get(j));
            }
        }
        return k;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Grid){
            Grid g = (Grid) obj;
            return g.getSingleLineValue()==this.getSingleLineValue();
        }
        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(getSingleLineValue());
    }
}