package java_assignments.assignments3;

import java.util.Scanner;

public class Parentheses {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String str;
        System.out.println("String: ");
        str = scanner.nextLine().trim();
        char[] charArray = str.toCharArray();

        Stack<Character> stk = new Stack<Character>();

        int count = 0;

        for (char ch : charArray) {
            switch (ch) {
            case '(': {
                stk.push(ch);
                count++;
            }
                break;

            case ')': {
                try {
                    char ch2 = stk.pop();
                    if (ch2 == '(') {
                        count--;
                    } else {
                        printMessage(false);
                        return;
                    }
                } catch (StackEmptyException e) {
                    printMessage(false);
                    return;
                }
            }
                break;

            case '{': {
                stk.push(ch);
                count++;
            }
                break;

            case '}': {
                try {
                    char ch2 = stk.pop();
                    if (ch2 == '{') {
                        count--;
                    } else {
                        printMessage(false);
                        return;
                    }
                } catch (StackEmptyException e) {
                    printMessage(false);
                    return;
                }
            }
                break;

            case '[': {
                stk.push(ch);
                count++;
            }
                break;

            case ']': {
                try {
                    char ch2 = stk.pop();
                    if (ch2 == '[') {
                        count--;
                    } else {
                        printMessage(false);
                        return;
                    }
                } catch (StackEmptyException e) {
                    printMessage(false);
                    return;
                }
            }
                break;

            case '<': {
                stk.push(ch);
                count++;
            }
                break;

            case '>': {
                try {
                    char ch2 = stk.pop();
                    if (ch2 == '<') {
                        count--;
                    } else {
                        printMessage(false);
                        return;
                    }
                } catch (StackEmptyException e) {
                    printMessage(false);
                    return;
                }
            }
                break;
            }

        }

        if(count == 0) printMessage(true);

        scanner.close();
        
    }

    private static void printMessage(boolean succ) {
        if (succ)
            System.out.println("Parenthesis properly balanced!");
        else
            System.out.println("Parenthesis not properly balanced!");
    }
}
