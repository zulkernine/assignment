package java_assignments.assignments6;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Patient {
    private String name;
    private String admissionDate;
    private String dispatchDate;
    private String assignedDoctorID;
    private boolean isDispatched;

    private String patientID; // patientID.txt will be record file

    Patient(String name, Doctor doctor) {
        this.name = name;
        patientID = name.substring(0, 3).toUpperCase() + System.currentTimeMillis();
        admissionDate = LocalDateTime.now().toString();

        assignedDoctorID = doctor.getID();
        doctor.addPatient(patientID);
        dispatchDate = "Not Available";

        File file = new File(ManageFolders.patientFoldersPath() + patientID + "_record.txt");
        if (!file.exists()) {
            try (FileWriter wrt = new FileWriter(file, true)) {
                wrt.write(Boolean.toString(isDispatched) + "\n");
                wrt.write(name + "\n");
                wrt.write(patientID + "\n");
                wrt.write(doctor.getName() + "\n" + doctor.getID() + "\n");
                wrt.write(admissionDate + "\n");
                wrt.write(dispatchDate + "\n");

                wrt.write("Test Results:\n");

            } catch (IOException e) {
                System.out.println(e);
            }
        }
        isDispatched = false;
    }

    Patient(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        isDispatched = Boolean.parseBoolean(scanner.nextLine());
        name = scanner.nextLine();
        patientID = scanner.nextLine();
        scanner.nextLine();// Ignore doctor's name;
        assignedDoctorID = scanner.nextLine();
        admissionDate = scanner.nextLine();
        dispatchDate = scanner.nextLine();
        scanner.close();
    }

    void addTestResult(TestResult tst) {
        File file = new File(ManageFolders.patientFoldersPath() + patientID + "_record.txt");
        try (FileWriter wrt = new FileWriter(file, true)) {

            wrt.write(tst.toString() + "\n");

        } catch (IOException e) {
            System.out.println(e);
        }
    }

    void printRecord() {
        File file = new File(ManageFolders.patientFoldersPath() + patientID + "_record.txt");
        try (Scanner scanner = new Scanner(file)) {
            boolean stillSubmitted = !Boolean.parseBoolean(scanner.nextLine());
            System.out.println("Name: " + scanner.nextLine());
            System.out.println("Patient ID: " + scanner.nextLine());
            System.out.println("Assigned Doctor: " + scanner.nextLine());
            System.out.println("Doctor's ID: " + scanner.nextLine());
            System.out.println("Admission Date: " + scanner.nextLine());
            System.out.println("Patient Left : " + (stillSubmitted ? "No" : "Yes"));
            System.out.println("Dispatch Date: " + scanner.nextLine());

            while (scanner.hasNextLine()) {
                System.out.println(scanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.out.println(e);
        }
    }

    String getId() {
        return patientID;
    }

    String getAssignedDoctorID() {
        return assignedDoctorID;
    }

    void disPatchPatient() {
        if (isDispatched) {
            System.out.println("Patient already dispatched on " + dispatchDate);
            return;
        }
        isDispatched = true;
        dispatchDate = LocalDateTime.now().toString();

        List<String> lines = Collections.emptyList();
        try {
            lines = Files.readAllLines(Paths.get(ManageFolders.patientFoldersPath() + patientID + "_record.txt"),
                    StandardCharsets.UTF_8);
        } catch (IOException e) {
            e.printStackTrace();
        }

        lines.set(6, dispatchDate);
        lines.set(0, Boolean.toString(isDispatched));

        try (FileWriter write = new FileWriter(
                new File(ManageFolders.patientFoldersPath() + patientID + "_record.txt"))) {
            for (String str : lines) {
                write.write(str + "\n");
            }
        } catch (IOException e) {
            System.out.println(e);
        }
    }

    @Override
    public String toString() {
        return "Name: " + name + "\t" + "ID: " + patientID + "\tDoctorID: " + assignedDoctorID + "\nAdmission date: "
                + admissionDate + "\nDispatch Date: " + dispatchDate + "\n";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Patient) {
            Patient d = (Patient) obj;

            return patientID.equals(d.patientID);
        } else if (obj instanceof String) {
            return patientID.equals(obj);
        }

        return false;
    }

    public boolean equals(String id) {
        return patientID.equals(id);
    }
}
