package assignment1.question2;

public class Vertex {
    //Number of missionary
    int misonary; 
    //Number of canibals
    int canibals;
    // true-> boat is at left side, false->boat is at right side
    //Missinary are on the left side of river at the beginning.
    boolean hasBoat;

    Vertex(int m,int c,boolean b){
        misonary = m;
        canibals = c;
        hasBoat = b;
    }

    Vertex traverseEdge(EdgeWeight e){
        int m,c;
        if(e.direction){
            m = this.misonary + e.misonary;
            c = this.canibals + e.canibals;
        }else{
            m = this.misonary - e.misonary;
            c = this.canibals - e.canibals;
        }

        return new Vertex(m, c, e.direction);
    }

    boolean isValid(){ return misonary>=canibals;}

    @Override
    public String toString() {
        return ("C:"+canibals+" M:"+misonary+" B"+hasBoat);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        Vertex v = (Vertex) o;
        return (misonary==v.misonary && canibals==v.canibals && hasBoat==v.hasBoat);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}
