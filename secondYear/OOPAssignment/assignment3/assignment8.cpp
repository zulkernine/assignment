/*
    Define a structure student with roll and score as attributes and with
    two member functions to take input and to show the data. Use the member
    functions to take data for a structure variable and to show.
    Write global function i) to modify score and ii) to show the data again.
*/

#include<iostream>
using namespace std;

struct student{
    int roll;
    int score;
    student(int r,int s):roll(r),score(s){}
    friend ostream &operator<<(ostream& stream,student &obj);
};

ostream &operator<<(ostream& stream, student &obj){
    stream<<"Roll:"<<obj.roll<<"  Score:"<<obj.score<<endl;
    return stream;
}

//Global Function
void modifyStudent(student &obj){
    cout<<"Enter new score:";
    cin>>obj.score;
}

int main(){
    int roll,score;
    cout<<"Roll:";cin>>roll;
    cout<<"Score:";cin>>score;
    student obj(roll,score);
    cout << "\n" << obj;
    modifyStudent(obj);
    cout<<"After modification:\n";
    cout<<obj;

    return 0;
}


