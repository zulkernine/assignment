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
    APPLICANT(){
        id = -1;
    }
    ~APPLICANT(){
        if(id!=-1) --idCount;
    }
    void setAppData(char* name,int score);

    inline int getId(){ return id; }

    void setApplicantName(char* name);
    inline char* getApplicantName(){ return name; }

    inline void setScore(int score){ this->score = score; }
    inline int getScore(){ return score; }

    static inline int numberOfApplicants(){
        return idCount;
    }

    friend ostream& operator<<(ostream& stream,const APPLICANT &application);
};

int APPLICANT::idCount = 0;

void APPLICANT::setApplicantName(char* name){
    int i = 0;
    do{
        this->name[i] = name[i];
        i++;
    } while (name[i] != '\0');
}

void APPLICANT::setAppData(char* name, int score){
    //set score
    this->score = score;

    //set name
    int i = 0;
    do{
        this->name[i] = name[i];
        i++;
    } while (name[i] != '\0');

    //set id
    this->id = (++APPLICANT::idCount);
}

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

    APPLICANT apl;
    apl.setAppData(buff,score);

    cout<<"Total no of applicant:"<<APPLICANT::numberOfApplicants()<<endl;
    cout<<"Application details:\n";
    cout<<apl;

    return 0;
}
