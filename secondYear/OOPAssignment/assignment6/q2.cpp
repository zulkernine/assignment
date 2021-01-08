/*
    Consider a class Student with roll, name and score as attributes. Support to take and display data is also
    there.  One wants to works with array of Student objects. May collect data for array elements, display those.
    In case index goes out of bounds, exception is to be raised with suitable message.
*/
#include<iostream>
#define MAX_SIZE 30
using namespace std;

int strlen(char* str);
void getLine(char* str, int size);
void strncpy(char* dest, char* source);

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
    Student(int r, char* n, int s){
        roll = r;
        strncpy(name, n);
        score = s;
    }

    inline int getRoll() const { return roll; }
    inline const char* getName() const { return name; }
    inline int getScore() const{ return score; }

    void setRoll(int r) { roll = r; }
    void setName(char* n){ strncpy(name, n); }
    void setScore(int s){ score = s; }

    friend ostream& operator<<(ostream& stream, const Student& s);
};

ostream& operator<<(ostream& stream, const Student& s){
    stream << "Roll: " << s.roll << "\n";
    stream << "Name: " << s.name << "\n";
    stream << "Score: " << s.score << "\n";

    return stream;
}

template<class T>
class Array{
    T* arr;
    const int capacity;//Max number of elments it can store
public:
    Array(int size) :capacity(size){
        arr = new T[capacity];
    }
    ~Array(){
        delete[] arr;
    }

    T& operator[](int index){
        if (index < 0 || index >= capacity){
            throw "Index Out Of Range";
        }

        return arr[index];
    }

};

int main(){
    int size;
    cout << "Array size: ";cin >> size;
    Array<Student> studentArr(size);

    for (int i = 0;i < size;i++){
        int roll, score;
        char name[MAX_SIZE];

        cout << "Roll: ";cin >> roll;
        cout << "Score: ";cin >> score;
        cout << "Name: ";getLine(name, MAX_SIZE);

        try{
            studentArr[i] = Student(roll, name, score);
        }
        catch (const char* exceptionMessage){
            cout << exceptionMessage << "\n";
        }
    }


    //Print the data, try to print out of range
    cout << "Displaying all student data:\n\n";
    for (int i = -1;i <= size;i++){
        cout<<"Index: "<<i<<"\n";
        try{
            cout << studentArr[i] << "\n";
        }
        catch (const char* exceptionMessage){
            cout << exceptionMessage << "\n";
        }

    }
}

int strlen(char* str){
    int len = 0;
    while (str[len++]);
    return len - 1;
}
void getLine(char* str, int size){
    do{
        cin.getline(str, size);
    } while (strlen(str) == 0);
}
void strncpy(char* dest, char* source){
    int i = 0;
    do{
        dest[i] = source[i];
    } while (source[i++]);
}
