package assignment1.question2;

import java.util.Objects;

public class Vertex {
    // Number of missionary
    int misonary;
    // Number of canibals
    int canibals;
    // true-> boat is at left side, false->boat is at right side
    // Missinary are on the left side of river at the beginning.
    boolean hasBoat;

    final int _hashCode;

    Vertex(int m, int c, boolean b) {
        misonary = m;
        canibals = c;
        hasBoat = b;

        _hashCode = Objects.hash(m, c, b);
    }

    Vertex traverseEdge(EdgeWeight e) {
        int m, c;
        if (e.direction) {
            m = this.misonary + e.misonary;
            c = this.canibals + e.canibals;
        } else {
            m = this.misonary - e.misonary;
            c = this.canibals - e.canibals;
        }

        return new Vertex(m, c, e.direction);
    }

    boolean isValid() {
        return (misonary >= canibals) 
        && (canibals >= 0) 
        && (misonary >= 0) 
        && (misonary <= 3) 
        && (canibals <= 3)
        && ((3-misonary) >= (3-canibals));
    }

    @Override
    public String toString() {
        return ("C:" + canibals + " M:" + misonary + " B: " + hasBoat);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        Vertex v = (Vertex) o;
        return (misonary == v.misonary && canibals == v.canibals && hasBoat == v.hasBoat);
    }

    @Override
    public int hashCode() {
        return this._hashCode;
    }
}
