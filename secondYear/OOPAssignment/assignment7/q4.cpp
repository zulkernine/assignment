/*
    Maintain   a   container   of   students   where   they   are   kept   in   the descending order of their scores.
    Take the help of suitable STL class
*/

#include<iostream>
#include <queue>
#include <vector>

using namespace std;

class Student{
    int roll;
    int score;
public:
    Student(int roll = -1, int score = 0){
        this->roll = roll;
        this->score = score;
    }

    inline int getRoll() const{ return roll; }
    inline int getScore() const{ return score; }
    inline void setScore(int s){ score = s; }

    friend ostream& operator<<(ostream& stream, const Student& st);
};
ostream& operator<<(ostream& stream, const Student& st){
    stream << "Roll: " << st.roll << " Score: " << st.score;
    return stream;
}

class CompareStudentByMarks{
public:
    bool operator() (const Student& s1, const Student& s2){
        return s1.getScore() < s2.getScore();
    }
};

template<typename T> void print_queue(T& q) {
    while (!q.empty()) {
        std::cout << q.top() << "\n";
        q.pop();
    }
    std::cout << '\n';
}

int main(){
    priority_queue<Student, vector<Student>, CompareStudentByMarks> studentQueue;

    while (true){
        cout << "1.Add student\n2.Display All Student\nctrl+c to exit\nOpt:-";
        int opt;
        cin >> opt;

        switch (opt){
        case 1:{
            int roll;int score;
            cout << "Roll: ";cin >> roll;
            cout << "Score: ";cin >> score;
            Student s(roll, score);
            studentQueue.push(s);
        };
              break;
        case 2:{
            cout << "\nAll students' score:\n";
            print_queue(studentQueue);
            cout << "\n";
        };
        default: cout << "Enter only 1 or 2\n";
        }
    }
}
