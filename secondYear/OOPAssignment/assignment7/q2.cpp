/*
    Create an array  of student objects where along with the supportmentioned in Q.1, one can remove an object
    with specific roll, sort the collection in the descending order and show the same; two studentcollections can
    also be combined. Take the help of suitable STL class.

    Features Required:
    1.Remove by roll (Done)
    2.Sort in descending order
    3.Combine two collection into one
*/

#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_SIZE 30
using namespace std;

class Student{
    int roll;
    char name[MAX_SIZE];
    int score;
public:
    Student(){
        roll = -1;
        name[0] = '\0';
        score = 0;
    }
    Student(int r, int s, char* n){
        roll = r;
        strcpy(name, n);
        score = s;
    }
    Student(int r, int s, string& n){
        roll = r;
        strcpy(name, n.c_str());
        score = s;
    }

    inline int getRoll() const { return roll; }
    inline string getName() const { return string(name); }
    inline int getScore() const{ return score; }

    void setRoll(int r) { roll = r; }
    void setName(char* n){ strcpy(name, n); }
    void setName(const string& n){ strcpy(name, n.c_str()); }
    void setScore(int s){ score = s; }

    friend ostream& operator<<(ostream& stream, const Student& s);
    friend class StudentArray;
};
ostream& operator<<(ostream& stream, const Student& s){
    stream << "Roll: " << s.roll << "\n";
    stream << "Name: " << s.name << "\n";
    stream << "Score: " << s.score << "\n";

    return stream;
}

class StudentArray :public vector<Student>{
    class SearchFunction{
        const int roll;
    public:
        SearchFunction(int r) :roll(r){}

        inline bool operator()(const Student& st) const{
            return (st.roll == roll);
        }
    };

public:
    StudentArray() :vector<Student>(){}
    StudentArray(int size) :vector<Student>(size){}

    //Returns the student object with highest score
    vector<Student>::iterator highestScore();

    //Returns an sudeents array whose name contrains the substring
    StudentArray findStudentsWithSubstring(string str);

    //Returns an sudeents array whose name doesn't contrains the substring
    StudentArray findStudentsWithoutSubstring(string str);

    //Remove the student corresponding to specified roll in the arguements
    void removeStudent(int roll);
};

vector<Student>::iterator StudentArray::highestScore(){
    vector<Student>::iterator maxScoreStudent = begin();
    for (vector<Student>::iterator itr = begin();itr != end();itr++){
        if (itr->score > maxScoreStudent->score) maxScoreStudent = itr;
    }
    return maxScoreStudent;
}
StudentArray StudentArray::findStudentsWithSubstring(string str){
    StudentArray arr;
    for (vector<Student>::iterator itr = begin();itr != end();itr++){
        string name(itr->name);//Convert the name array to STL string
        size_t pos = name.find(str);
        if (pos != string::npos) arr.push_back(*itr);
    }
    return arr;
}
StudentArray StudentArray::findStudentsWithoutSubstring(string str){
    StudentArray arr;
    for (vector<Student>::iterator itr = begin();itr != end();itr++){
        string name(itr->name);//Convert the name array to STL string
        size_t pos = name.find(str);
        if (pos == string::npos) arr.push_back(*itr);
    }
    return arr;
}
void StudentArray::removeStudent(int roll){
    vector<Student>::iterator itr = find_if(begin(), end(), SearchFunction(roll));
    if (itr == end()){
        cout << "No Students-data available corresponding to given roll-" << roll << "\n";
    }    
else{
        erase(itr);
    }
}

int main(){
    StudentArray arr;
    int size = 5;//for testing
    cout << "Enter 5 student record: \n";
    for (int i = 0;i < 5;i++){
        int r, s;string name("");
        cout << "SR:" << i + 1 << "\n";
        cout << "Name: ";
        while (name == "") getline(cin, name);

        cout << "Roll: ";cin >> r;
        cout << "Score: ";cin >> s;

        Student st(r, s, name);
        arr.push_back(st);
    }

    cout << "Number of Objects in the list: " << arr.size() << "\n";
    cout << "Student with highest score:\n" << *(arr.highestScore()) << "\n";

    //Find students with a substring in name
    string substr = "";
    cout << "Enter the substring to find: ";
    while (substr == "") getline(cin, substr);
    StudentArray subArr = arr.findStudentsWithSubstring(substr);
    cout << "Found Student details: \n";
    for (auto itr = subArr.begin();itr != subArr.end();itr++){
        cout << (*itr) << "\n";
    }

    //Find students without a substring in name
    substr = "";
    cout << "Enter the substring to find(which name excludes): ";
    while (substr == "") getline(cin, substr);
    StudentArray subArr2 = arr.findStudentsWithoutSubstring(substr);
    cout << "Found Student details: \n";
    for (auto itr = subArr2.begin();itr != subArr2.end();itr++){
        cout << (*itr) << "\n";
    }

    return 0;
}

