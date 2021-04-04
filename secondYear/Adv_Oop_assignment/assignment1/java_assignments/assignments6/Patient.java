package java_assignments.assignments6;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.Scanner;

public class Patient {
    private String name;
    private String admissionDate;
    private String assignedDoctorID;
 
    private String patientID; //patientID.txt will be record file

    Patient(String name,Doctor doctor){
        this.name = name;
        patientID = name.substring(0,3).toUpperCase()+ System.currentTimeMillis();
        admissionDate = LocalDateTime.now().toString();

        assignedDoctorID = doctor.getID();
        doctor.addPatient(this);

        File file = new File(patientID + "_record.txt");
        try (FileWriter wrt = new FileWriter(file, true)) {
            wrt.write("Name: "+name + "\n");
            wrt.write("ID: "+ patientID + "\n");
            wrt.write("Doctor: "+doctor.getName()+"\tDoctor's ID: "+doctor.getID()+"\n");
            wrt.write("Admission Date: "+admissionDate);
            wrt.write("Test Results:\n");

        } catch (IOException e) {
            System.out.println(e);
        }
    }

    void addTestResult(TestResult tst){
        File file = new File(patientID+"_record.txt");
        try(FileWriter wrt = new FileWriter(file,true)){

            wrt.write(tst.toString() + "\n" );

        }catch(IOException e){
            System.out.println(e);
        }
    }

    void printRecord(){
        File file = new File(patientID + "_record.txt");
        try(Scanner scanner = new Scanner(file)){
            while(scanner.hasNextLine()){
                System.out.println(scanner.nextLine());
            }
        }catch(FileNotFoundException e){
            System.out.println(e);
        }
    }

    String getId(){ return patientID; }
    String getAssignedDoctorID(){ return assignedDoctorID; }

}
