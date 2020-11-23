/*
    Design a STUDENT class to store roll, name, course, admission date and marks in 5 subjects. 
    Provide methods corresponding to admission (marks are not available then), 
    receiving marks and preparing mark sheet. 
    Support must be there to show the number of students who have taken admission.
*/

#include <iostream>
#include <ctime>
using namespace std;

class STUDENT
{
    int roll;
    char name[30];
    int course; //id of course
    time_t admissionDate;
    int marks[5];
    static int numberOfStudent;

public:
    STUDENT() : roll(-1), course(0)
    {
        for (int i = 0; i < 5; i++)
            marks[i] = 0;
        name[0] = '\0';
        numberOfStudent++;
    }
    ~STUDENT(){
        numberOfStudent--;
    }

    void admit(int roll, char *name)
    {
        this->roll = roll;
        int i = 0;
        for ( i = 0; name[i] != '\0'; i++)
            this->name[i] = name[i];
        this->name[i] = '\0';

        admissionDate = time(0);
    }
    void setMarks(){
        int d;
        for(int i=0;i<5;i++){
            cout<<"Marks of subject code-"<<i<<" : ";
            cin>>d;
            if(d<0 || d>100) i--;
            else marks[i]=d;
        }
    }
    void marksheet(){
        cout<<"\n\n";
        cout<<"Roll:"<<roll<<" Name:"<<name<<endl;
        for(int i=0;i<5;i++){
            cout<<"Marks for subject code-"<<i<<" : "<<marks[i]<<endl;
        }
        cout<<endl;
    }
    char* getAdmissionDate(){
        struct tm *date;
        date = localtime(&admissionDate);
        char* dateString = asctime(date);
        return dateString;
    }
    static inline int getNumberOfStudent(){ return numberOfStudent; }
};

int STUDENT::numberOfStudent = 0;

int main(){
    STUDENT st;
    int roll;char *buff;
    buff = new char[50];

    cout<<"Roll: ";cin>>roll;
    cin.ignore();cin.clear();
    cout<<"Name: ";cin.getline(buff,50);
    st.admit(roll,buff);
    st.setMarks();

    cout<<"\nNumber of students: "<<STUDENT::getNumberOfStudent()<<endl;
    st.marksheet();
    buff = st.getAdmissionDate();
    cout<<"Admission date: "<<buff;
    return 0;
}
