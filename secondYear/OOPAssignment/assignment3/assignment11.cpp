/*
    Create an APPLICANT class with application id (auto generated as last id +1), name and score.
    Support must be there to receive applicant data, show applicant details and to find out number of applicants
*/

#include<iostream>
using namespace std;

class APPLICANT{
    static int idCount;
    int id;
    char name[30];
    int score;

public:
    APPLICANT(int score,char* name):score(score){
        ++idCount;
        this->id = idCount;

        int i=0;
        do{
            this->name[i] = name[i];
            i++;
        }while(name[i]!='\0');
    }
    ~APPLICANT(){
        --idCount;
    }

    static inline int numberOfApplicants(){
        return idCount;
    }

    friend ostream& operator<<(ostream& stream,const APPLICANT &application);
};

int APPLICANT::idCount = 0;

ostream& operator<<(ostream& stream,const APPLICANT &application){
    stream<<"ID: "<<application.id<<"  Score: "<<application.score<<endl;
    stream<<"Name: "<<application.name<<endl;
    return stream;
}

int main(){
    int score;char buff[50];
    cout<<"applicant score:";cin>>score;
    cin.ignore();cin.clear();
    cout<<"Name:";cin.getline(buff,50);

    APPLICANT apl(score,buff);

    cout<<"Total no of applicant:"<<APPLICANT::numberOfApplicants()<<endl;
    cout<<"Application details:\n";
    cout<<apl;

    return 0;
}
