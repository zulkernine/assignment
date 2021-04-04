package java_assignments.assignments6;

import java.util.ArrayList;

public class Doctor {
    String name;
    String doctorID;
    ArrayList<String> patients;

    Doctor(String name){
        this.name = name;
        doctorID = name.substring(0, 3).toUpperCase() + System.currentTimeMillis();
        patients = new ArrayList<String>();
    }

    void addPatient(Patient pt){
        patients.add(pt.getId());
    }

    void removePatient(Patient pt){
        patients.remove(pt.getId());
    }

    String getID(){ return doctorID; }
    String getName(){ return name; }
}
