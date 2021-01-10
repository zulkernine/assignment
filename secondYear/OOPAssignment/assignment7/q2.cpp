/*
    Create an array  of student objects where along with the supportmentioned in Q.1, one can remove an object
    with specific roll, sort the collection in the descending order and show the same; two studentcollections can
    also be combined. Take the help of suitable STL class.

    Features Required:
    1.Remove by roll (Done)
    2.Sort in descending order and show the same (Done)
    3.Combine two collection into one (Assume students with same roll will not repeat in a collection) (Done)
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
    class SearchByRoll{
        const int roll;
    public:
        SearchByRoll(int r) :roll(r){}

        inline bool operator()(const Student& st) const{
            return (st.roll == roll);
        }
    };

public:
    StudentArray() :vector<Student>(){}
    StudentArray(const StudentArray& arr) :vector<Student>(arr){}
    StudentArray(int size) :vector<Student>(size){}

    //Returns the student object with highest score
    vector<Student>::iterator highestScore();

    //Returns an sudeents array whose name contrains the substring
    StudentArray findStudentsWithSubstring(string str);

    //Returns an sudeents array whose name doesn't contrains the substring
    StudentArray findStudentsWithoutSubstring(string str);

    //Remove the student corresponding to specified roll in the arguements
    void removeStudent(int roll);

    //sort by roll in descending order
    void sortDescending();

    //Show the list
    friend ostream& operator<<(ostream& stream, const StudentArray& arr);
    friend StudentArray operator+(const StudentArray& arr1, const StudentArray& arr2);
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
    vector<Student>::iterator itr = find_if(begin(), end(), SearchByRoll(roll));
    if (itr == end()){
        cout << "No Students-data available corresponding to given roll-" << roll << "\n";
    }
    else{
        erase(itr);
    }
}
void StudentArray::sortDescending(){
    sort(this->begin(), this->end(), [](const Student& st1, const Student& st2){
        return st1.getRoll() < st2.getRoll();
        });
}

ostream& operator<<(ostream& stream, const StudentArray& arr){
    for (auto itr = arr.begin();itr != arr.end();itr++){
        stream << (*itr) << "\n";
    }
    return stream;
}
StudentArray operator+(const StudentArray& arr1, const StudentArray& arr2){
    StudentArray arg1(arr1), arg2(arr2), result(arr1.size() + arr2.size());

    arg1.sortDescending();
    arg2.sortDescending();

    set_union(arg1.begin(), arg1.end(), arg2.begin(), arg2.end(), result.begin(), [](const Student& st1, const Student& st2){
        return st1.getRoll() < st2.getRoll();
        });

    auto last = unique(result.begin(), result.end(), [](const Student& st1, const Student& st2){
        return st1.getRoll() == st2.getRoll();
        });

    result.resize(distance(result.begin(),last));

    return result;
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

    // //Find students with a substring in name
    // string substr = "";
    // cout << "Enter the substring to find: ";
    // while (substr == "") getline(cin, substr);
    // StudentArray subArr = arr.findStudentsWithSubstring(substr);
    // cout << "Found Student details: \n";
    // cout << subArr << "\n";

    // //Find students without a substring in name
    // substr = "";
    // cout << "Enter the substring to find(which name excludes): ";
    // while (substr == "") getline(cin, substr);
    // StudentArray subArr2 = arr.findStudentsWithoutSubstring(substr);
    // cout << "Found Student details: \n";
    // cout << subArr2 << "\n";

    // cout << "\n\nSorted Student List:\n";
    // arr.sortDescending();
    // cout << arr << "\n";

    // cout << "Enter a roll to remove: ";
    // int roll;cin >> roll;

    // arr.removeStudent(roll);
    // cout << "After removing a student:\n";
    // cout << arr << "\n";

    StudentArray arr2;
    size = 3;//for testing
    cout << "Enter 3 more student record to merge(repeat some): \n";
    for (int i = 0;i < size;i++){
        int r, s;string name("");
        cout << "SR:" << i + 1 << "\n";
        cout << "Name: ";
        while (name == "") getline(cin, name);

        cout << "Roll: ";cin >> r;
        cout << "Score: ";cin >> s;

        Student st(r, s, name);
        arr.push_back(st);
    }

    StudentArray combined;
    combined = arr + arr2;

    cout << "Combined List:\n";
    cout << combined << "\n";

    return 0;
}

