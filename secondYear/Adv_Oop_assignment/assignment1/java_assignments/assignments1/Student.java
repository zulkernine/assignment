package java_assignments.assignments1;

import java.util.Date;

class Student{
    String roll;
    String name;
    String course;
    Date admissionDate;
    int marks[];

    Student(){
        marks = new int[5];
    }

    Student(String n,String r,String c){
        name = new String(n);
        roll = new String(r);
        course = new String(c);
    }

    void setAdmissionDate(long timeStamp){
        admissionDate = new Date();
        admissionDate.setTime(timeStamp); 
    }

    


}
