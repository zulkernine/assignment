public class Employee {
    private String name;
    private String id;
    private String deptCode;
    private double salary;
    private String grade;

    Employee() {
        name = "";
        id = "";
        deptCode = "";
        grade = "";
        salary = 0;
    }

    public String getName() {
        return name;
    }

    public String getId() {
        return id;
    }

    public String getDeptCode() {
        return deptCode;
    }

    public double getSalary() {
        return salary;
    }

    public String getGrade() {
        return grade;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setDeptCode(String deptCode) {
        this.deptCode = deptCode;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }

    @Override
    public String toString() {
        return "ID: " + id + "\tName: " + name + "\nSalary: " + Double.toString(salary) + "\nDept. Code: " + deptCode
                + "\nGrade: " + grade + "\n";
    }

}
