import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class ViewEmployee extends JPanel {
    private ArrayList<Employee> empList;
    private DefaultListModel<Employee> tempList;
    private JTextField searchBar;

    ViewEmployee(ArrayList<Employee> empList) {
        this.empList = empList;
        tempList = new DefaultListModel<>();

        setUpWindow();
    }

    private void setUpWindow() {
        setLayout(new BorderLayout());

        JButton viewAll = new JButton("View All");
        viewAll.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                tempList.clear();
                tempList.addAll(empList);
                searchBar.setText("");
            }
        });

        JPanel searchPanel = new JPanel();
        searchBar = new JTextField(20);
        searchBar.setPreferredSize(new Dimension(20, 30));
        searchPanel.add(searchBar);
        JButton searchButton = new JButton(
                new ImageIcon(new ImageIcon("./search.png").getImage().getScaledInstance(20, 20, Image.SCALE_DEFAULT)));
        searchButton.setPreferredSize(new Dimension(30, 30));
        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                handleSearch();
            }
        });
        viewAll.setPreferredSize(new Dimension(90, 30));
        searchPanel.add(searchButton);
        searchPanel.add(viewAll);
        add(searchPanel,BorderLayout.NORTH);

        JList<Employee> showList = new JList<Employee>(tempList);
        showList.setCellRenderer(new EmployeeRendere());
        add(new JScrollPane(showList), BorderLayout.CENTER);

    }

    private class EmployeeRendere extends JTextArea implements ListCellRenderer<Employee> {

        @Override
        public Component getListCellRendererComponent(JList<? extends Employee> list, Employee emp, int index,
                boolean isSelected, boolean cellHasFocus) {
            setText(emp.toString());
            return this;
        }

    }

    private void handleSearch() {
        tempList.clear();
        for (Employee e : empList) {
            if (e.getId().equals(searchBar.getText())) {
                tempList.addElement(e);
                return;
            }
        }

        JOptionPane.showMessageDialog(this.getParent(), "No Employee Found", "Not Found",
                JOptionPane.INFORMATION_MESSAGE);
    }
}
