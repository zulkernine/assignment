package question4;

import java.util.Objects;

public class Vertex {
    final int first;
    final int second;
    
    final int _hashCode;

    Vertex(int c1, int c2) {
        first = c1;
        second = c2;
        _hashCode = Objects.hash(c1,c2);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        Vertex v = (Vertex) o;
        return (first == v.first && second == v.second);
    }

    @Override
    public int hashCode() {
        return this._hashCode;
    }

    @Override
    public String toString() {
        return ("i: "+first+"\tj: "+second);
    }
}
