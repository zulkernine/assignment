/*
    Students come to mark sheet collection desk and are served in firstcome first served basis. Implement the
    scenario. Take the help ofsuitable STL class
*/

#include<iostream>
#include<queue>
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
};

int main(){
    queue<Student> studentqueue;

    while (true){
        int opt;
        cout << "Number of students awaiting in line now: " << studentqueue.size() << "\n";
        cout << "Choose among the options:\n";
        cout << "1.Add students in the queue for marksheets\n";
        cout << "2.Give marksheet to the student\n";
        cout << "Option:-";
        cin >> opt;

        switch (opt){
        case 1:{
            int roll;
            cout << "Roll of Student:- ";cin >> roll;
            Student s(roll);
            studentqueue.push(s);
        } break;
        case 2:{
            if (studentqueue.empty()){
                cout << "No student in the line! Add some student first\n";
            }
            else{
                int score = rand() % 100;
                Student st = studentqueue.front();
                st.setScore(score);
                studentqueue.pop();

                cout << "\nScore of roll - " << st.getRoll() << " is : " << st.getScore() << "\n\n";
            }

        } break;
        default:{
            cout << "Enter option only between 1 and 2\n";
        }
        }
    }
}
