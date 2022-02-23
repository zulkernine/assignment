import java.util.Scanner;

public class Q3Main {
    public static int countMatches(String str, String target) {
        return (str.length() - str.replace(target, "").length()) / target.length();
    }

    public static void main(String[] args) {
        String str;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Type the string: ");
        str = scanner.nextLine();


        System.out.println("Number of times 'a' appears: " + countMatches(str, "a"));
        System.out.println("Number of times 'and' appears: " + countMatches(str, "and"));
        System.out.println("Starts with 'The' ? Ans: " + str.startsWith("The"));
        System.out.print("Array of char: ");
        for(var s : str.toCharArray()) System.out.print(s+", ");
        
        System.out.print("\nAll tokens: ");
        for(var s: str.split("[ @.]")) System.out.print(s+", ");
        System.out.println();

        scanner.close();
    }
}
