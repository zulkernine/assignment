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

        while(true){
            int opt = getOption(scanner);

            switch(opt){
                case 1:{
                    String patientName,doctorID;
                    System.out.print("Patient Name: ");
                    patientName = scanner.nextLine();
                    System.out.print("Assigned doctor ID: ");
                    doctorID = scanner.nextLine();
                    Patient pt = new Patient(patientName,searchFromList(doctorList, doctorID));
                    patientList.add(pt);
                    System.out.println("Patient admitted. Patient ID: " + pt.getId());

                }break;

                case 2:{
                    System.out.print("Doctor's Name: ");
                    String name = scanner.nextLine();
                    Doctor doc = new Doctor(name);
                    doctorList.add(doc);

                    System.out.println("New doctor employeed. Doctor ID: " + doc.getID());
                }break;

                case 3:{
                    String id;
                    System.out.print("Patient ID: ");
                    id = scanner.nextLine();

                    Patient pt = searchFromList(patientList, id);
                    pt.disPatchPatient();

                    System.out.println("Patient "+pt.getId()+"\t successfully dispatched.");
                }break;

                case 4:{
                    
                }

                case 8:{
                    saveDoctorRecords(doctorList);

                    return;
                }
                
                default:{
                    System.out.println(
                        "Option index must be within 1-8 both inclusive."
                    );
                }
            }
        }



         
    }

    private static void checkPatientRecord(ArrayList<Patient> patients){
        File pFolder = new File(ManageFolders.patientFoldersPath());
        for(File pFile: pFolder.listFiles()){
            try {
                patients.add(new Patient(pFile));
            } catch (FileNotFoundException e) {
                System.out.println(e + "File Name: "+ pFile.getAbsolutePath() );
            }
        }
    }

    private static void checkDoctorRecord(ArrayList<Doctor> doctor) {
        File dFolder = new File(ManageFolders.doctorFoldersPath());
        for (File dFile : dFolder.listFiles()) {
            try {
                doctor.add(new Doctor(dFile));
            } catch (FileNotFoundException e) {
                System.out.println(e + "File Name: " + dFile.getAbsolutePath());
            }
        }
    }

    private static void saveDoctorRecords(ArrayList<Doctor> doctors){
        for(var doctor: doctors){
            doctor.save();
        }
    }

    private static int getOption(Scanner sc){
        System.out.println(
            "Choose Option:- "+
            "1.Admit patient"+
            "2.Employee New Doctor"+
            "3.Dispatch Patient"+
            "4.Submit Patient Test Result"+
            "5.Print Patient Record"+
            "6.Display all Doctors' details"+
            "7.Display all Patients record"+
            "8.Exit"+
            "Option:- "
        );
        
        return Integer.parseInt(sc.nextLine());
    }

    private static <T> T searchFromList(ArrayList<T> list,String id){
        for(T item: list){
            if(item.equals(id)) return item;
        }
        return null;
    }

}
