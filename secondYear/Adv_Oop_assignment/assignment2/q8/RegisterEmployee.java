import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class RegisterEmployee extends JPanel {
    private Employee emp;
    private JTextField name, empId, salary;
    private JComboBox grades, deptCode;

    private ArrayList<Employee> empList;

    RegisterEmployee(ArrayList<Employee> empList) {
        emp = new Employee();
        this.empList = empList;
        setUpWindow();
    }

    public Employee getEmp() {
        return emp;
    }

    private void setUpWindow() {
        setLayout(new GridLayout(0, 2));

        add(new JLabel("Name: "));
        name = new JTextField(5);
        add(name);

        add(new JLabel("Employee ID: "));
        empId = new JTextField(5);
        add(empId);

        add(new JLabel("Salary: "));
        salary = new JTextField(5);
        add(salary);

        add(new JLabel("Grade: "));
        String gradeList[] = { "A", "B", "C" };
        grades = new JComboBox<String>(gradeList);
        grades.setEditable(false);
        add(grades);

        add(new JLabel("Department: "));
        String deptList[] = { "BCSE", "BEEE", "IEEE", "ETCE", "FTBE" };
        deptCode = new JComboBox<String>(deptList);
        deptCode.setEditable(false);
        add(deptCode);

        grades.setSelectedIndex(0);
        deptCode.setSelectedIndex(0);

        JButton reset = new JButton("Reset");
        reset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                resetField();
            }
        });
        add(reset);

        JButton save = new JButton("Save");
        save.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                saveData();
            }
        });
        add(save);

    }

    private void validateAndSetID() {
        String id = empId.getText();
        for (Employee e : empList) {
            if (e.getId().equals(id)) {
                JOptionPane.showMessageDialog(this.getParent(),
                        "Another employee " + e.getName() + " already exist with same ID!", "ID already exist",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
        }

        emp.setId(id);
    }

    private void saveData() {
        validateAndSetID();
        emp.setName(name.getText().trim());
        try {
            emp.setSalary(Double.parseDouble(salary.getText().trim()));
        } catch (Exception e) {
            salary.setText("");
            JOptionPane.showMessageDialog(this.getParent(), "Salary must be a number", "Salary",
                    JOptionPane.WARNING_MESSAGE);
            return;
        }
        emp.setDeptCode((String) deptCode.getSelectedItem());
        emp.setGrade((String) grades.getSelectedItem());

        int opt = JOptionPane.showConfirmDialog(this.getParent(), "Save this employee data?", "Confirmation",
                JOptionPane.YES_NO_OPTION);
        
        if(opt == JOptionPane.NO_OPTION) return;
        
        empList.add(emp);
        System.out.println(emp);

        resetField();
    }

    private void resetField() {
        emp = new Employee();
        name.setText("");
        salary.setText("0.0");
        empId.setText("");
        grades.setSelectedIndex(0);
        deptCode.setSelectedIndex(0);
    }
}
