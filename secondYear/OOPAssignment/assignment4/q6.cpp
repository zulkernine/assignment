/*
    For each student roll, name and phone number are to be maintained. For each subject store
    subject code, name. A student may choose number of subjects from a list of subjects.
    A subject may be chosen by number of students. Given a roll number system must able to display
    the subjects chosen by the student and also be able to display the students corresponding to a
    subject code. Design the classes and implement the system.
*/

class SUBJECT{
    const int subCode;
    char name[50];

public:
    //Initialise the code -1 to imply invalid subject
    SUBJECT(char* _name, int code = -1) :subCode(code){}

    friend class SubjectList;
};

class SubjectList{
    SUBJECT* list;
    int size;
public:
    SubjectList(int _size=10);//Allocate memory for the "list" array
    
    //if the code is unique and doesn't exist in the list, ads to the list
    void addSubject(int code,char* name);
};


class STUDENT{
    char name[30];
    int roll;
    int phoneNumber;
    SUBJECT subjects[5];

    //Returns true if subject corresponding to subcode exist in subjects array
    bool hasSubject(int subCode);
public:
    STUDENT(char* _name, int num, int _roll=-1);//Initialise with data, roll=-1 implies invalid student object

    //Displays all the subject of the student
    void displaySubject();
    friend class StudentList;
};

class StudentList{
    STUDENT* list;
    int size;
    SubjectList subjectList;

public:
    //FInds and return a pointer for corresponding roll. If no student exist 
    //for given roll, returns null
    STUDENT* findStudent(int roll);
    //Initialise the list and allocate memory for it
    StudentList(int _size=100);

    //Display all student who have the subject corresponding to subCode,
    //It uses STUDENT::hadSubject() to look into the array
    void displayStudentForSubject(int subCode);

    //Allows user to modify the available subjects list; 
    void modifySubjectList();

    //If student of corresponding roll exist, it allows to modify the subject list of that student
    //Uses StudentList::findStudent() function internally
    void modifySubjectOfStudent(int roll);

    //Finds the student for given roll using StudentList:findStudent() and if exist, displays all the
    //subject using STUDENT::displaySubjects()
    void subjectsOfStudent(int roll);
};
