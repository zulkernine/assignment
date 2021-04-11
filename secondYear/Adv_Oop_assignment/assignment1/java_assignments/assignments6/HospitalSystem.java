package java_assignments.assignments6;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class HospitalSystem {
    public static void main(String[] args) {
        ManageFolders.checkFolders();

        ArrayList<Patient> patientList = new ArrayList<Patient>();
        checkPatientRecord(patientList);

        ArrayList<Doctor> doctorList = new ArrayList<Doctor>();
        checkDoctorRecord(doctorList);

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n");
            int opt = getOption(scanner);
            System.out.println("\n\n");

            switch (opt) {
            case 1: {
                String patientName, doctorID;
                System.out.print("Patient Name: ");
                patientName = scanner.nextLine();
                System.out.print("Assigned doctor ID: ");
                doctorID = scanner.nextLine();
                Patient pt = new Patient(patientName, searchFromList(doctorList, doctorID));
                patientList.add(pt);
                System.out.println("Patient admitted. Patient ID: " + pt.getId());

            }
                break;

            case 2: {
                System.out.print("Doctor's Name: ");
                String name = scanner.nextLine();
                Doctor doc = new Doctor(name);
                doctorList.add(doc);

                System.out.println("New doctor employeed. Doctor ID: " + doc.getID());
            }
                break;

            case 3: {
                String id;
                System.out.print("Patient ID: ");
                id = scanner.nextLine();

                Patient pt = searchFromList(patientList, id);
                if (pt == null) {
                    System.out.println("No patient exist with given ID!");
                } else {
                    pt.disPatchPatient();
                    Doctor doc = searchFromList(doctorList, pt.getAssignedDoctorID());
                    doc.removePatient(pt.getId());

                    System.out.println("Patient " + pt.getId() + "\t successfully dispatched.");
                }
            }
                break;

            case 4: {
                String id;
                System.out.print("Patient ID: ");
                id = scanner.nextLine();

                Patient pt = searchFromList(patientList, id);
                if (pt == null) {
                    System.out.println("No patient exist with given ID");
                } else {
                    String name, value, unit;

                    System.out.print("Test name: ");
                    name = scanner.nextLine();
                    System.out.print("Test result(value): ");
                    value = scanner.nextLine();
                    System.out.print("Unit of the result value: ");
                    unit = scanner.nextLine();

                    pt.addTestResult(new TestResult(name, value, unit));
                    System.out.println("Test result added to patient : " + pt.getId());
                }
            }
                break;

            case 5: {
                String id;
                System.out.print("Patient ID: ");
                id = scanner.nextLine();

                Patient pt = searchFromList(patientList, id);
                if (pt == null) {
                    System.out.println("No patient exist with given ID");
                } else {
                    pt.printRecord();
                }
            }
                break;

            case 6: {
                for (var doctor : doctorList) {
                    System.out.println(doctor);
                }
            }
                break;

            case 7: {
                for (var pat : patientList) {
                    System.out.println(pat + "\n");
                }
            }
                break;

            case 8: {
                saveDoctorRecords(doctorList);

                return;
            }

            default: {
                System.out.println("Option index must be within 1-8 both inclusive.");
            }
            }
        }

    }

    private static void checkPatientRecord(ArrayList<Patient> patients) {
        File pFolder = new File(ManageFolders.patientFoldersPath());
        try {
            for (File pFile : pFolder.listFiles()) {
                try {
                    patients.add(new Patient(pFile));
                } catch (FileNotFoundException e) {
                    System.out.println(e + "File Name: " + pFile.getAbsolutePath());
                }
            }
        } catch (Exception e) {
            System.out.println("Can't set Patient's file: \n" + e);
            e.printStackTrace();
        }
        
    }

    private static void checkDoctorRecord(ArrayList<Doctor> doctor) {
        File dFolder = new File(ManageFolders.doctorFoldersPath());
        try {
            for (File dFile : dFolder.listFiles()) {
                try {
                    doctor.add(new Doctor(dFile));
                } catch (FileNotFoundException e) {
                    System.out.println(e + "File Name: " + dFile.getAbsolutePath());
                }
            }
        } catch (Exception e) {
            System.out.println("Can't set doctor's list:\n" + e);
        }
    }

    private static void saveDoctorRecords(ArrayList<Doctor> doctors) {
        for (var doctor : doctors) {
            doctor.save();
        }
    }

    private static int getOption(Scanner sc) {
        System.out.print("Choose Option:- \n" + "1.Admit patient\n" + "2.Employee New Doctor\n" + "3.Dispatch Patient\n"
                + "4.Submit Patient Test Result\n" + "5.Print Patient's all Record\n" + "6.Display all Doctors' details\n"
                + "7.Display all Patients Details\n" + "8.Exit\n" + "Option:- ");

        return Integer.parseInt(sc.nextLine());
    }

    private static <T> T searchFromList(ArrayList<T> list, String id) {
        for (T item : list) {
            if (item.equals(id))
                return item;
        }
        return null;
    }

}
