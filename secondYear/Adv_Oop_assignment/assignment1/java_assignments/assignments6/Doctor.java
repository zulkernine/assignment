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
        patients = new ArrayList<String>();
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

    void addPatient(String  id){
        patients.add(id);
    }

    void removePatient(String id){
        patients.remove(id);
    }

    String getID(){ return doctorID; }
    String getName(){ return name; }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Doctor){
            Doctor d = (Doctor) obj;

            return doctorID.equals(d.doctorID);
        }else if(obj instanceof String){
            return doctorID.equals(obj);
        }
        
        return false; 
    }
    
    @Override
    public String toString() {
        String str = "";
        str = "Name: "+name+"\t\tID: "+doctorID+"\t" + "Assigned patients' ID: ";
        for(String id : patients) str += (id + ",");
        str += "\n";
        return str ;
    }
}
