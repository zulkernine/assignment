package java_assignments.assignments1;

import java.time.*;
import java.util.Comparator;

public class Student{
    private static int totalNumberOfAdmission;
    private String roll;
    private String name;
    private String course;
    private LocalDateTime admissionDate;
    private int marks[]; //0<=score<=100

    Student(){
        marks = new int[5];
    }

    Student(String n,String c){
        name = new String(n);
        course = new String(c);

        marks = new int[5];
    }

    protected void setAdmissionDate(LocalDateTime d){
        admissionDate = d;
        Student.totalNumberOfAdmission++;
    }
    void setMark(int index,int score){
        if(score<0 || score > 100){
            System.out.println("Invalid Score! Score must be:  0<=score<=100");
            return;
        }

        try{
            marks[index] = score;
        }catch(IndexOutOfBoundsException e){
            System.out.println("Invaid index passed! Error:");
            System.out.println(e.getMessage());
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
    void setName(String n){
        if(n!=null && n.length()>0){
            name = new String(n);
        }else{
            System.out.println("Invalid name passed");
        }
    }
    protected void setRoll(String r){
        if(r!=null && r.length()>0){
            roll = new String(r);
        }else{
            System.out.println("INvalid Roll");
        }
    }
    void setCourse(String c) {
        if (c != null && c.length() > 0) {
            course = new String(c);
        } else {
            System.out.println("INvalid Course");
        }
    }
    
    public static Comparator<Student> StudentTotalScore = new Comparator<Student>(){
        public int compare(Student s1,Student s2){
            int totalScore1=0,totalScore2=0;

            for(int s:s1.marks){
                totalScore1 += s;
            }
            for (int s : s2.marks) {
                totalScore2 += s;
            }

            return totalScore1-totalScore2 ;
        }
    };


    void displayMarksheet(){
        if(admissionDate == null){
            System.out.println("This Student is not admitted yet!");
        }else{
            System.out.print("Name: " + this.name );
            System.out.println(" \tRoll: " + this.roll );
            System.out.println("Course: "+this.course );
            
            String subjects[] = { "Bengali","English","History","Geography","Science" };
            
            System.out.println("Marks:");
            for(int i=0;i<5;i++){
                System.out.print(subjects[i] + ":" + marks[i] +"\t");
            }
            
        }
    }
    String getCourse(){
        return course;
    }
    String getName(){ return name; }
    String getRoll(){ return roll; }
    
    static public int getNumberOfAdmission(){
        return Student.totalNumberOfAdmission;
    }

    @Override
    public String toString() {
        int totalScore1 = 0;
        for (int s : marks) {
            totalScore1 += s;
        }
        
        return ("Roll: "+roll+"  Name: "+name+"\t Total Score: "+totalScore1);
    }

}
