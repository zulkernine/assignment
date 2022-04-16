package question2;

/**
 * possible edges: (1,0),(0,1),(2,0),(1,1),(0,2) with b true or false,
 */

public class EdgeWeight {
    // Number of missionary on boat
    int misonary;
    // Number of canibals on boat
    int canibals;
    // true-> boat is going to left side, false->boat is going to right side
    boolean direction;

    EdgeWeight(int m,int c,boolean b){
        misonary = m;
        canibals = c;
        direction = b;
    }

}
