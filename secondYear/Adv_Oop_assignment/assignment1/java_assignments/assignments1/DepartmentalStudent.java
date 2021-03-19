package java_assignments.assignments1;

import java.time.*;

public class DepartmentalStudent extends Student {
    private String departmentName;

    DepartmentalStudent() {
        super();
    }

    DepartmentalStudent(String name, String course, String deptName) {
        super(name, course);
        departmentName = new String(deptName);
    }

    void admitStudent(int serialNumber) {
        LocalDateTime d = LocalDateTime.now();
        this.setAdmissionDate(d);
        String roll = "";
        roll += departmentName;
        int y = d.getYear() % 100;
        roll = roll + y;

    }
}
