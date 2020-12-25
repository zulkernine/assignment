/*
    For each student roll, name and phone number are to be maintained. For each subject store
    subject code, name. A student may choose number of subjects from a list of subjects.
    A subject may be chosen by number of students. Given a roll number system must able to display
    the subjects chosen by the student and also be able to display the students corresponding to a
    subject code. Design the classes and implement the system.
*/
#include<iostream>
using namespace std;

class SUBJECT{
    int subCode;
    char name[50];

public:
    //Initialise the code -1 to imply invalid subject
    SUBJECT(char* _name, int code);
    inline int getCode() const{ return subCode; }

    friend class SubjectList;
    friend ostream& operator<<(ostream& stream, const SUBJECT& sub);
};

SUBJECT::SUBJECT(char* _name = nullptr, int code = -1) :subCode(code){
    int i = 0;
    if (_name){
        while (_name[i] != '\0' && i < 49){
            name[i] = _name[i];
            i++;
        }
    }
    name[i] = '\0';

}

ostream& operator<<(ostream& stream, const SUBJECT& sub){
    if (sub.subCode != -1){
        stream << "Subject Name: " << sub.name << "\n";
        stream << "Subject Code: " << sub.subCode << "\n";
    }
    else stream << "";

    return stream;
}

class SubjectList{
    static int lastCode;
    SUBJECT* list;
    int size;
public:
    SubjectList(int);//Allocate memory for the "list" array
    ~SubjectList();

    //adds to the list
    int addSubject(char* name);
    inline int getSize() const{ return size; }
    void print();

    SUBJECT operator[](int i);
};

int SubjectList::lastCode = 0;

SUBJECT SubjectList::operator[](int i){
    if (i >= 0 && i < size) return list[i];
}

SubjectList::SubjectList(int _size = 20){
    list = new SUBJECT[_size];
    size = _size;
}

SubjectList::~SubjectList(){
    delete[] list;
}

int SubjectList::addSubject(char* name){
    int i = 0;
    while (i < size && list[i].subCode != -1) i++;
    if (i < size){
        SUBJECT sub(name, lastCode++);
        list[i] = sub;
        return lastCode - 1;
    }
    else{
        cout << "Subject List is Full.No more subject can be added :(\n";
        return -1;
    }
}

void SubjectList::print(){
    for (int i = 0;i < size;i++){
        if (list[i].subCode != -1){
            cout << "Index " << i << "\n";
            cout << list[i];
        }
        else break;
    }
}

class STUDENT{
    char name[50];
    int roll;
    int phoneNumber;
    SUBJECT subjects[5];

    //Returns true if subject corresponding to subcode exist in subjects array
    bool hasSubject(int subCode);
public:
    STUDENT();
    STUDENT(char* _name, int num, int _roll = -1);//Initialise with data, roll=-1 implies invalid student object
    //Displays all the subject of the student
    void displaySubject();
    void print();

    friend class StudentList;
};

STUDENT::STUDENT(char* _name, int contactNum, int _roll){
    int i = 0;
    while (_name[i] != '\0' && i < 49){
        name[i] = _name[i];
        i++;
    }
    name[i] = '\0';

    phoneNumber = contactNum;
    roll = _roll;
}

STUDENT::STUDENT(){
    name[0] = '\0';
    phoneNumber = -1;
    roll = -1;
}

bool STUDENT::hasSubject(int subCode){
    for (int i = 0;i < 5;i++){
        if (subjects[i].getCode() == subCode) return true;
    }
    return false;
}

void STUDENT::displaySubject(){
    cout << "All Subjects of " << name << " :\n";
    for (int i = 0;i < 5;i++){
        cout << subjects[i];
    }
}

void STUDENT::print(){
    cout << "Name: " << name << "\n";
    cout << "Roll: " << roll << "\n";
    cout << "Contact Number: " << phoneNumber << "\n";

    cout << "Selected Subjects:\n";
    displaySubject();
    cout << "\n";
}

class StudentList{
    static int lastRoll;
    STUDENT* list;
    int size;
    SubjectList subjectList;

    //FInds and return a pointer for corresponding roll. If no student exist 
    //for given roll, returns null
    STUDENT* findStudent(int roll);
public:

    //Initialise the list and allocate memory for it
    StudentList(int _size);
    ~StudentList(){ delete[] list; }

    //Display all student who have the subject corresponding to subCode,
    //It uses STUDENT::hadSubject() to look into the array
    void displayStudentForSubject(int subCode);

    //Allows user to modify the available subjects list; 
    void modifySubjectList();

    //Add sTudent to the list array
    void addStudent();

    //Show all the subjects
    void showAllSubjects(){ subjectList.print(); }

    //If student of corresponding roll exist, it allows to modify the subject list of that student
    //Uses StudentList::findStudent() function internally
    // void modifySubjectOfStudent(int roll);

    //Finds the student for given roll using StudentList:findStudent() and if exist, displays all the
    //subject using STUDENT::displaySubjects()
    void subjectsOfStudent(int roll);
};
int StudentList::lastRoll = 0;

StudentList::StudentList(int _size = 100) :size(_size){
    list = new STUDENT[size];
    subjectList = SubjectList(50);
}

STUDENT* StudentList::findStudent(int roll){
    for (int i = 0;i < size;i++){
        if (list[i].roll == roll) return (list + i);
        else if (list[i].roll == -1) break;
    }
    return nullptr;
}

void StudentList::displayStudentForSubject(int subCode){
    for (int i = 0;i < size;i++){
        if (list[i].roll != -1){
            if (list[i].hasSubject(subCode)){
                cout << "Roll: " << list[i].roll << "\nName: " << list[i].name << "\n";
            }
            else break;
        }
    }
}

void StudentList::modifySubjectList(){
    while (true){
        cin.ignore();cin.clear();
        cout << "1.Print Current List\n2.Add Subject\n3.Exit\nOption:";
        int opt;
        cin >> opt;
        switch (opt){
        case 1: this->subjectList.print();break;
        case 2:{
            char temp[50];
            cout << "New Subject Name:";
            cin.ignore();cin.clear();
            cin.getline(temp, 50);

            int code = subjectList.addSubject(temp);
            if (code != -1) cout << "Succesfully Added! It's code: " << code << "\n";
        }
              break;
        case 3: return;
        default:{
            cout << "Option Must be between 1-3\n";
        }
        }
    }
}

void StudentList::addStudent(){
    int i = 0;
    while (list[i].roll != -1) i++;
    if (i < size){
        list[i].roll = ++lastRoll;
        cout << "Full Name: ";
        cin.clear();
        cin.getline(list[i].name, 50);
        cout << "Contact Number: ";cin >> list[i].phoneNumber;

        subjectList.print();
        cout << "Print Any 5 index of subject: ";
        for (int j = 0;i < 5;){
            cout << "Index: ";
            int in;cin >> in;
            if (in >= 0 && in < subjectList.getSize()){
                list[i].subjects[j] = subjectList[in];
                j++;
            }
            else cout << "Index must be positive or 0\n";
        }

        cout << "One Student Added:\n";
        list[i].print();

    }
    else{
        cout << "Student List is full\nNomore Student can be added :(\n\n";
    }
}

// void StudentList::modifySubjectOfStudent(int roll){

// }

void StudentList::subjectsOfStudent(int roll){
    STUDENT* s = findStudent(roll);

    s->displaySubject();
}


int main(){
    StudentList sl;
    cout << "Please add atleast 5 subject:\n";
    sl.modifySubjectList();

    while (true){
        cout << "\n\n------------------------------------------------------------\n";
        cout << "Choose An Option:\n";
        cout << "0.Exit the program\n1.Add Student\n2.Modify Subject List\n";
        cout << "3.Find All Students For a subject\n4.Show All Subjects\n";
        cout << "5.Show all subjects of a student\n";
        cout << "Option:- ";
        int opt;
        cin >> opt;

        switch (opt){
        case 0:{
            cout << "\n\nExiting the program\n\n";
            exit(0);
        }
        case 1:{
            sl.addStudent();
        }
              break;
        case 2: sl.modifySubjectList();
            break;
        case 3:{
            cout << "Subject Code:";
            int c;cin >> c;
            sl.displayStudentForSubject(c);
        }
              break;
        case 4:sl.showAllSubjects();break;
        case 5:{
            cout << "Roll: ";int r;cin >> r;
            sl.subjectsOfStudent(r);
        }
        default: cout << "Choose an option between 0 and 5 (both inclusive)\n\n";
        }
    }

}

/*
    This program has bugs about IO,
*/