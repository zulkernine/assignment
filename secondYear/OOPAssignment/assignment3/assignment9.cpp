/*
    9. Design a class TIME which stores hour, minute and second. The class
    should have the methods to support the following:
    ◦ User may give the time value in 24-hour format.
    ◦ User may give the time value in AM/PM format
    ◦ Display the time in 24-hour format.
    ◦ Display the time in AM/PM format.
    ◦ User may like to add minute with a time value.
*/

#include<iostream>
#include <sstream>
#include <regex> 
#include <algorithm>
#include <iomanip>

using namespace std;

ostream& setw2(ostream& stream){
    stream << std::setfill('0') << std::setw(2);
    return stream;
}

class TIME{
    int hour, minute, second;
public:
    TIME(string _str){
        stringstream str(_str);
        char ch;
        str >> hour;
        if (hour >= 24){
            cout << "Invalid HOur\n";
            exit(1);
        }
        str >> ch;
        str >> minute;
        if (minute >= 60){
            cout << "Invalid Minute\n";
            exit(1);
        }
        str >> ch;
        str >> second;
        if (minute >= 60){
            cout << "Invalid Second\n";
            exit(1);
        }

        string ampm;
        getline(str, ampm);
        ampm = std::regex_replace(ampm, std::regex("^ +| +$|( ) +"), "$1");
        if (ampm.length() > 0){
            transform(ampm.begin(), ampm.end(), ampm.begin(), ::toupper);
            if (ampm == "PM"){
                hour += 12;
            }
            else if(ampm!="AM"){
                throw "Invalid arguement";
            }
        }
    }
    TIME():hour(0),minute(0),second(0) 
    {}
    void view(){
        string meridian = hour>12?"PM":"AM";
        cout << "Time- " << setw2 << (hour > 12 ? (hour - 12) : hour) << ":" << setw2 << minute << ":" << setw2 << second << " " << meridian << endl;
    }
    void view24(){
        cout << "Time- " << setw2 << (hour) << ":" << setw2 << minute << ":" << setw2 << second << endl;
    }

    friend TIME operator+(TIME& t,int min){
        TIME tr;
        tr.hour = t.hour + min/60 + (min%60 + t.minute)/60;
        tr.minute = (min % 60 + t.minute) % 60;
        return tr;
    }
};

int main(){
    string str;
    cout << "Input time- ";
    getline(cin, str);

    TIME t(str);
    t.view();
    t.view24();

    t = t + 136;
    t.view();
    t.view24();
    return 0;
}



