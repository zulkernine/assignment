package java_assignments.assignments6;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Doctor {
    String name;
    String doctorID;
    ArrayList<String> patients;

    private File recordFile;

    Doctor(String name){
        this.name = name;
        doctorID = name.substring(0, 3).toUpperCase() + System.currentTimeMillis();
        patients = new ArrayList<String>();

        recordFile = new File(ManageFolders.doctorFoldersPath() + doctorID + ".txt");
    }

    Doctor(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        recordFile = file;

        name = scanner.nextLine();
        doctorID = scanner.nextLine();
        while(scanner.hasNextLine()){
            patients.add(scanner.nextLine());
        }

        scanner.close();
    }

    void save(){
        try (PrintWriter wrt = new PrintWriter(recordFile)) {
            wrt.println(name);
            wrt.println(doctorID);
            for(String id:patients){
                wrt.println(id);
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    void addPatient(Patient pt){
        patients.add(pt.getId());
    }

    void removePatient(Patient pt){
        patients.remove(pt.getId());
    }

    String getID(){ return doctorID; }
    String getName(){ return name; }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Doctor)) return false;

        Doctor d = (Doctor) obj;

        return  doctorID.equals(d.doctorID);
    }

    public boolean equals(String ID) {
        return ID.equals(doctorID);
    }
}
