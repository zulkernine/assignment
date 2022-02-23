import java.util.Scanner;

public class Q4Main {
    public static void main(String[] args) {
        int i = 10, j;

        CustomInteger integer = new CustomInteger(i); // numeric to object
        j = integer.toInt();

        System.out.println("Numeric to string: " + CustomInteger.toString(j));
        CustomInteger int2 = new CustomInteger("234");
        System.out.println("String to object: " + int2); // also object to string

    }

}

class CustomInteger {
    private int i;

    // numeric to object
    CustomInteger(int i) {
        this.i = i;
    }

    CustomInteger() {
        this.i = 0;
    }

    // String to object
    CustomInteger(String str) {
        Scanner sc = new Scanner(str);
        if (sc.hasNextInt()) {
            this.i = sc.nextInt();
        } else {
            sc.close();
            throw new IllegalArgumentException("No Integer found");
        }
        sc.close();
    }

    // Object to numeric
    int toInt() {
        return i;
    }

    // numeric to string
    static String toString(int i) {
        return String.format("%d", i);
    }

    // Object to string
    @Override
    public String toString() {
        return String.format("%d", this.i);
    }

}
