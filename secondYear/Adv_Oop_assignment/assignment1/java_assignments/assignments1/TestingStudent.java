package java_assignments.assignments1;

import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.Scanner;

public class TestingStudent {
    public static void main(String[] args) {
        ArrayList<DepartmentalStudent> students = new ArrayList<DepartmentalStudent>();

        Scanner scanner = new Scanner(System.in);
        while (true) {
            printOption();
            int opt = 0;

            try {
                opt = scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println(e.getMessage());
            } catch (Exception e) {
                System.out.println(e.getLocalizedMessage());
            }

            // scanner.nextLine();//Remove the white space from buffer
            switch (opt) {
            case 1: {
                String name, course, dept;

                clearInputBuffer(scanner);

                System.out.print("Name: ");
                name = scanner.nextLine();
                System.out.print("Course: ");
                course = scanner.nextLine();
                System.out.print("Department name(BCSE/ETCE/BEEE/FTBE): ");
                dept = scanner.next();

                DepartmentalStudent student = new DepartmentalStudent(name, course, dept);
                int lastRoll = lastRollOfDept(dept, students);
                student.admitStudent(lastRoll + 1);
                students.add(student);
            }
                break;

            case 2: {
                String roll;

                clearInputBuffer(scanner);

                System.out.print("Roll of student: ");
                roll = scanner.next();
                DepartmentalStudent student = null;
                for (DepartmentalStudent st : students) {
                    if (st.getRoll().equals(roll)) {
                        student = st;
                        break;
                    }
                }

                if (student == null) {
                    System.out.println("Student not found");
                } else {
                    students.remove(student);
                    System.out.println("Student with roll:" + roll + " has been removed!");
                }

            }
                break;

            case 3: {
                String dept;
                clearInputBuffer(scanner);

                System.out.print("Deartment name(BCSE/ETCE/BEEE/FTBE): ");
                dept = scanner.next();

                ArrayList<DepartmentalStudent> tempDept = new ArrayList<DepartmentalStudent>();

                for (DepartmentalStudent st : students) {
                    if (st.getDepartment().equals(dept)) {
                        tempDept.add(st);
                    }
                }

                Collections.sort(tempDept, Student.StudentTotalScore);

                for (DepartmentalStudent st : tempDept) {
                    System.out.println(st);
                }
            }
                break;

            case 4: {
                Collections.sort(students, Student.StudentTotalScore);

                for (DepartmentalStudent st : students) {
                    System.out.println(st);
                }
            }
                break;

            case 5: {
                Runtime runtime = Runtime.getRuntime();
                System.out.println("Current Free Memory: " + ((double) runtime.freeMemory() / 1048576) + "  MB");
                runtime.gc();
                System.out.println(
                        "After calling gc(), Free Memory: " + ((double) runtime.freeMemory() / 1048576) + "  MB");
            }
                break;

            case 6: {
                String roll;
                clearInputBuffer(scanner);

                System.out.print("Roll of student:");
                roll = scanner.next();

                DepartmentalStudent student = null;
                // Search the student
                for (DepartmentalStudent st : students) {
                    if (st.getRoll().equals(roll)) {
                        student = st;
                        break;
                    }
                }

                if (student != null) {
                    String subjects[] = { "0.Bengali", "1.English", "2.History", "3.Geography", "4.Science" };
                    while (true) {
                        System.out.println("Enter subject no. to set corresponding marks(-1 to exit):");
                        for (String sub : subjects) {
                            System.out.println(sub);
                        }
                        System.out.print("Option:- ");
                        int index = scanner.nextInt();

                        if (index == -1)
                            break;
                        else if (index >= 0 && index < 5) {
                            int score;
                            System.out.print("Marks in " + subjects[index] + ": ");
                            score = scanner.nextInt();

                            student.setMark(index, score);
                        }
                    }
                } else {
                    System.out.println("No student found with roll:" + roll);
                }
            }
                break;

            case 7: {
                String roll;
                clearInputBuffer(scanner);

                System.out.print("Roll of student:");
                roll = scanner.next();

                DepartmentalStudent student = null;
                // Search the student
                for (DepartmentalStudent st : students) {
                    if (st.getRoll().equals(roll)) {
                        student = st;
                        break;
                    }
                }

                if (student == null) {
                    System.out.println("No student registered with roll:" + roll);
                } else {
                    student.displayMarksheet();
                }
            }
                break;

            case 8: {
                System.out.println("Total Number of Student: " + Student.getNumberOfAdmission());
            }
                break;

            case 9: {
                scanner.close();
                return;
            }

            default: {
                System.out.println("Choose valid option between 1-7(Both inclusive)");
            }

            }
        }

    }

    private static int lastRollOfDept(String dept, ArrayList<DepartmentalStudent> students) {
        int roll = 0;
        for (DepartmentalStudent st : students) {
            if (st.getDepartment().equals(dept)) {
                int r = Integer.parseInt(st.getRoll().substring(6));
                if (r > roll)
                    roll = r;
            }
        }
        return roll;
    }

    private static void printOption() {
        System.out.println("\n\nChose Option:");
        System.out.println("1.Add Student");
        System.out.println("2.Remove a Student");
        System.out.println("3.Display Student of certain department(Sorted)");
        System.out.println("4.Display all student sorted by score");
        System.out.println("5.Check Memory");
        System.out.println("6.Set Marks");
        System.out.println("7.Display Marksheet");
        System.out.println("8.Total Number of student");
        System.out.println("9.Exit");
        System.out.print("Option:- ");
    }

    private static void clearInputBuffer(Scanner scanner) {

        if (scanner.hasNextLine())
            scanner.nextLine();
    }
}
