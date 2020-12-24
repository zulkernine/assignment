/*
    Each cricketer has name, date of birth and matches played. Cricketer may be a bowler or batsman.
    
    For a bowler, number of wickets taken, average economy is stored.
    
    For a batsman, total runs scored,average score is stored.
    
    A double wicket pair is formed taking a bowler and a batsman.
    
    An all-rounder is both a bowler and batsman.
    
    Support must be there to show the details of a cricketer, bowler, batsmen,
    all-rounder and the pair.
*/
#include<iostream>
using namespace std;

class Cricketer{
protected:
    char name[50]; //Stores name
    char date[20]; // stores dates string in UTC format
    int numberOfMatchesPlayed;
public:
    Cricketer(char* _name,char* _date);

    //Displays these basic info(name,dae of birth,numbers of match played)
    virtual void displayInfo();

    //Increament the numberOfMatches played by 1
    inline void increamentMatches();
};

void Cricketer::displayInfo(){
    cout<<"Name: "<<name<<endl;
    cout<<"DOB: "<<date<<endl;
    cout<<"Total matches played:"<<numberOfMatchesPlayed<<endl;
}

void Cricketer::increamentMatches(){
    numberOfMatchesPlayed++;
}

class Batsman: virtual public Cricketer{
protected:
    int totalRuns;
    float averageRun;

public:
    //Overrides the base class virtual function to display additional info with those in base class
    virtual void displayInfo();

    //Add to total run
    void addRun(int newRun);
};

void Batsman::displayInfo(){
    Cricketer::displayInfo();
    cout<<"Total Run: "<<totalRuns<<endl;
    cout<<"Average Run: "<<averageRun<<endl;
}

void Batsman::addRun(int newRun){
    if(newRun<0){
        throw string("Invalid Arguement: Negative Run not allowed\n");
    }else{
        totalRuns += newRun;
        averageRun = totalRuns/numberOfMatchesPlayed;
    }
}

class Bowler: virtual public Cricketer{
protected:
    int numberOfWickets;
    float averageEconomy;
public:
    //Overrides the base class virtual function to display additional info with those in base class
    virtual void displayInfo();

    //Add to total wicket
    void addWicket(int newWicket);
};

void Bowler::displayInfo(){
    Cricketer::displayInfo();
    cout << "Total Wickets: " << numberOfWickets << endl;
    cout << "Average Economy: " << averageEconomy << endl;
}

void Bowler::addWicket(int w){
    if(w<0){
        throw string("Invalid Arguement: Number of wickets can't be negative\n");
    }else{
        numberOfWickets += w;
        averageEconomy = numberOfWickets/numberOfMatchesPlayed;
    }
}

class Alrounder: public Batsman,public Bowler{
public:
    //Overrides the base class virtual function to display additional info with those in base class
    void displayInfo();
};

void Alrounder::displayInfo(){
    Cricketer::displayInfo();
    Batsman::displayInfo();
    Bowler::displayInfo();
}

class DoubleWicketPair{
    Batsman batsman;
    Bowler bowler;

public:
    DoubleWicketPair(Batsman bt,Bowler bl);
    void displayInfo();
};

void DoubleWicketPair::displayInfo(){
    cout<<"Batsman:"<<endl;
    batsman.displayInfo();
    cout<<"\nBowler:"<<endl;
    bowler.displayInfo();
}
