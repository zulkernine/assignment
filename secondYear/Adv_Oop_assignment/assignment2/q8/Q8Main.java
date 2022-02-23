import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

class Q8Main {
    private static ArrayList<Employee> empList;
    static {
        empList = new ArrayList<Employee>();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        JPanel panel = new JPanel(new CardLayout());
        JTabbedPane tabs = new JTabbedPane();

        RegisterEmployee regEmp = new RegisterEmployee(empList);
        tabs.addTab("Register Employee", regEmp);
        ViewEmployee viewEmp = new ViewEmployee(empList);
        tabs.addTab("View Employee", viewEmp);
        
        frame.add(tabs);

        frame.setVisible(true);

    }
}
