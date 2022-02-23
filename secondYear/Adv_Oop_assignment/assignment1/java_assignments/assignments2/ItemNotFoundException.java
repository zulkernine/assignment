package java_assignments.assignments2;

public class ItemNotFoundException extends Exception {

    /**
     *
     */
    private static final long serialVersionUID = 7822148420906130569L;
    @Override
    public String getMessage() {
        return super.getMessage() + "Item Not Found!";
    }
    
}
