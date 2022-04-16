package question3;

import java.util.Objects;

public class Vertex {
    final int first;
    final int second;
    final int c1;
    final int c2;

    final int _hashCode;

    Vertex(int c1, int c2) {
        this.c1 = c1;
        this.c2 = c2;
        first = 0;
        second = 0;
        _hashCode = Objects.hash(c1,c2,first,second);
    }

    Vertex(int c1,int c2,int f,int s){
        this.c1 = c1;
        this.c2 = c2;
        first = f;
        second = s;
        _hashCode = Objects.hash(c1, c2,f,s);
    }

    Vertex traverseEdge(Edges e){
        int f,s;
        f = first + e.first;
        s = second + e.second;

        if(f>=0 && s>=0 && f<=c1 && s<= c2){
            return new Vertex(c1,c2,f,s);
        }

        return null;
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
        return ("first: "+first+"\tsecond: "+second);
    }
}
