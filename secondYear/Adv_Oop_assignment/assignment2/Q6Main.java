import java.util.ArrayList;
import java.util.Scanner;

public class Q6Main {
    private static ArrayList<Person> persons;
    static {
        persons = new ArrayList<Person>();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n");
            printOption();
            switch (Integer.parseInt(scanner.nextLine())) {
                case 0: {
                    scanner.close();
                    System.exit(0);
                }

                case 1: {
                    Students s = new Students();
                    s.setData(scanner);
                    persons.add(s);
                    System.out.println("One student added. Students roll: " + s.getRoll());
                }
                    break;

                case 2: {
                    Faculty f = new Faculty();
                    f.setData(scanner);
                    persons.add(f);
                    System.out.println("One faculty employed. Employee ID: " + f.getId());
                }
                    break;

                case 3: {
                    System.out.print("Unique ID(roll or emp ID): ");
                    Person p = findPerson(scanner.nextLine().trim());
                    p.updateData(scanner);
                }
                    break;

                case 4: {
                    System.out.print("Unique ID(roll or emp ID): ");
                    Person p = findPerson(scanner.nextLine().trim());
                    System.out.println(p);
                }
                    break;

                case 5: {
                    for (var p : persons)
                        System.out.println(p);
                }
                    break;

                case 6: {
                    System.out.print("Unique ID(roll or emp ID): ");
                    Person p = findPerson(scanner.nextLine().trim());
                    p.updateAddress(scanner);
                }
                    break;

                default:
                    System.out.println("Option must be within 0-6 both inclusive!");
            }
        }

    }

    private static void printOption() {
        System.out.print("0.Exit\n" + "1.Add Student\n" + "2.Add Faculty\n" + "3.Update data\n" + "4.Diplay data\n"
                + "5.Show all persons details\n" + "6.Update address\n" + "Option:- ");
    }

    private static Person findPerson(String uid) {
        for (Person p : persons) {
            if (p.equals(uid))
                return p;
        }
        return null;
    }
}

class Address {
    private String premiseNumber;
    private String street;
    private String city;
    private int pin;
    private String state;

    Address(String number, String street, String city, String state, int pin) {
        premiseNumber = number;
        this.street = street;
        this.city = city;
        this.pin = pin;
        this.state = state;
    }

    Address() {
    }

    String getPremiseNumber() {
        return premiseNumber;
    }

    String getStreet() {
        return street;
    }

    String getCity() {
        return city;
    }

    int getPin() {
        return pin;
    }

    String getState() {
        return state;
    }

    void setPremisesNumber(String num) {
        premiseNumber = num;
    }

    void setStreet(String name) {
        street = name;
    }

    void setCity(String name) {
        city = name;
    }

    void setPin(int pin) {
        this.pin = pin;
    }

    void setState(String name) {
        state = name;
    }

    void setData(Scanner scanner) {
        System.out.print("Premise no. ");
        premiseNumber = scanner.nextLine();
        System.out.print("Street name: ");
        street = scanner.nextLine();
        System.out.print("City: ");
        city = scanner.nextLine();
        System.out.print("PIN/ZIP code: ");
        pin = Integer.parseInt(scanner.nextLine());
        System.out.print("State name: ");
        state = scanner.nextLine();
    }

    @Override
    public String toString() {
        String str = premiseNumber + ", " + street + ", " + city + ", " + state + "-" + Integer.toString(pin);

        return str;
    }
}

abstract class Person {
    private String name;
    private Address address;
    private String phoneNumber;
    private String email;

    Person() {
    }

    void setData(Scanner scanner) {
        System.out.print("Name: ");
        name = scanner.nextLine();
        System.out.print("Phone number:");
        phoneNumber = scanner.nextLine();
        System.out.print("Email: ");
        email = scanner.nextLine();
        address = new Address();
        address.setData(scanner);
    }

    void setName(String name) {
        this.name = name;
    }

    void setPhoneNumber(String num) {
        this.phoneNumber = num;
    }

    void setEmail(String mail) {
        this.email = mail;
    }

    void setAddress(Address addr) {
        this.address = addr;
    }

    String getName() {
        return name;
    }

    Address getAddress() {
        return address;
    }

    String getPhoneNumber() {
        return phoneNumber;
    }

    String getEmail() {
        return email;
    }

    void updateData(Scanner scanner) {
        if (willUpdate("Name", scanner)) {
            System.out.print("Name: ");
            name = scanner.nextLine();
        }

        if (willUpdate("Phone Number", scanner)) {
            System.out.print("Phone number: ");
            phoneNumber = scanner.nextLine();
        }

        if (willUpdate("Email", scanner)) {
            System.out.print("Email: ");
            email = scanner.nextLine();
        }

        if (willUpdate("Address", scanner)) {
            updateAddress(scanner);
        }

    }

    void updateAddress(Scanner scanner) {
        if (willUpdate("Premises Number", scanner)) {
            System.out.print("Premises number: ");
            address.setPremisesNumber(scanner.nextLine());
        }
        if (willUpdate("Street name", scanner)) {
            System.out.print("Street name: ");
            address.setStreet(scanner.nextLine());
        }
        if (willUpdate("City", scanner)) {
            System.out.print("City: ");
            address.setCity(scanner.nextLine());
        }
        if (willUpdate("PIN/ZIP", scanner)) {
            System.out.println("PIN/ZIP code: ");
            address.setPin(Integer.parseInt(scanner.nextLine()));
        }
        if (willUpdate("State", scanner)) {
            System.out.print("Sate");
            address.setState(scanner.nextLine());
        }
    }

    protected static boolean willUpdate(String attribute, Scanner scanner) {
        System.out.print("Update " + attribute + " ?(y/n): ");
        return scanner.nextLine().trim().toLowerCase().equals("y");
    }

    @Override
    public String toString() {
        String str = "Name: " + name + "\nEmail: " + email + "\nPhone Number: " + phoneNumber + "\nAddress: "
                + address.toString() + "\n";
        return str;
    }

}

class Students extends Person {
    private String course;
    private String roll;

    Students() {
        roll = Long.toString(System.currentTimeMillis());
    }

    public String getRoll() {
        return roll;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    @Override
    void setData(Scanner scanner) {
        System.out.print("Course: ");
        course = scanner.nextLine();
        super.setData(scanner);
    }

    @Override
    void updateData(Scanner scanner) {
        if (willUpdate("course", scanner)) {
            System.out.print("Course: ");
            course = scanner.nextLine();
        }
        super.updateData(scanner);
    }

    @Override
    public String toString() {
        return "Roll: " + roll + "\tCourse: " + course + "\n" + super.toString();
    }

    public boolean equals(Object obj) {
        if (obj instanceof String) {
            return roll.equals((String) obj);
        } else if (obj instanceof Students) {
            return ((Students) obj).roll.equals(roll);
        }

        return false;
    }
}

class Faculty extends Person {
    private String id;
    private String department;
    private String specialization;

    Faculty() {
    }

    public String getId() {
        return id;
    }

    public String getDepartment() {
        return department;
    }

    public String getSpecialization() {
        return specialization;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public void setSpecialization(String specialization) {
        this.specialization = specialization;
    }

    @Override
    void setData(Scanner scanner) {
        System.out.print("Department: ");
        department = scanner.nextLine();
        System.out.print("Specialization: ");
        specialization = scanner.nextLine();

        super.setData(scanner);
        id = department.substring(0, 4).toUpperCase() + Long.toString(System.currentTimeMillis() % 100000);
    }

    @Override
    void updateData(Scanner scanner) {
        if (willUpdate("Department", scanner)) {
            System.out.print("Department: ");
            department = scanner.nextLine();
        }
        if (willUpdate("Specialization", scanner)) {
            System.out.print("Specialization: ");
            specialization = scanner.nextLine();
        }
        super.updateData(scanner);
    }

    @Override
    public String toString() {
        return "ID: " + id + "\tDepartment: " + department + "\nSpecialization: " + specialization + "\n"
                + super.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof String) {
            return id.equals((String) obj);
        } else if (obj instanceof Faculty) {
            return ((Faculty) obj).id.equals(id);
        }

        return false;
    }
}
