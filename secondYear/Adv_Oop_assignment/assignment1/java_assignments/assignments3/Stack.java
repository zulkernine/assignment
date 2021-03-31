package java_assignments.assignments3;

public class Stack<Type> {
    private class Node{
        public Type data;
        Node next;

        Node(Type d){
            data = d;
            next = null;
        }
    }

    private Node head;

    void push(Type data){
        Node node = new Node(data);
        if(head == null) head = node;
        else {
            node.next = head;
            head = node;
        }
    }

    Type pop() throws StackEmptyException{
        if(head == null){
            throw new StackEmptyException();
        }else{
            Type data = head.data;
            Node n = head;
            head = head.next;
            n.next = null;

            return data;
        }
        
    }
}

class StackEmptyException extends Exception{

    /**
     *
     */
    private static final long serialVersionUID = -8526779306682606335L;
    @Override
    public String getMessage() {
        return "Stack is Empty";
    }

}
