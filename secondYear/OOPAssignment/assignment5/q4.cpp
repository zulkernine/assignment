/*
    Each cricketer has name, date of birth and matches played. Cricketer may be a bowler or alrounder.

    For a bowler, number of wickets taken, average economy is stored.

    For a batsman, total runs scored,average score is stored.

    A double wicket pair is formed taking a bowler and a batsman.

    An all-rounder is both a bowler and batsman.

    Support must be there to show the details of a cricketer, bowler, batsmen,
    all-rounder and the pair.
*/
#include<iostream>
using namespace std;

void strncpy(char* dest, char* source){
    int i = 0;
    do{
        dest[i] = source[i];
    } while (source[i++]);
}

int strlen(char* str){
    int len = 0;
    while (str[len++]);
    return len - 1;
}

class Cricketer{
protected:
    char name[50]; //Stores name
    char date[20]; // stores dates string in UTC format
    int numberOfMatchesPlayed;
public:
    Cricketer(char* _name, char* _date){
        strncpy(name, _name);
        strncpy(date, _date);
        numberOfMatchesPlayed=0;
    }

    //Displays these basic info(name,dae of birth,numbers of match played)
    virtual void displayInfo();

    //Increament the numberOfMatches played by 1
    inline void increamentMatches();
};

void Cricketer::displayInfo(){
    cout << "Name: " << name << endl;
    cout << "DOB: " << date << endl;
    cout << "Total matches played:" << numberOfMatchesPlayed << endl;
}

void Cricketer::increamentMatches(){
    numberOfMatchesPlayed++;
}

class Batsman : virtual public Cricketer{
protected:
    int totalRuns;
    float averageRun;

public:
    Batsman(char* name, char* date) :Cricketer(name, date){
        totalRuns = 0;
        averageRun = 0;
    }
    //Overrides the base class virtual function to display additional info with those in base class
    virtual void displayInfo();

    //Add to total run
    void addRun(int newRun);
};

void Batsman::displayInfo(){
    Cricketer::displayInfo();
    cout << "Total Run: " << totalRuns << endl;
    cout << "Average Run: " << averageRun << endl;
}

void Batsman::addRun(int newRun){
    if (newRun < 0){
        throw string("Invalid Arguement: Negative Run not allowed\n");
    }
    else{
        totalRuns += newRun;
        increamentMatches();
        averageRun = (float)(totalRuns) / numberOfMatchesPlayed;
    }
}

class Bowler : virtual public Cricketer{
protected:
    int numberOfWickets;
    float averageEconomy;
public:
    Bowler(char* name, char* date) :Cricketer(name, date){
        numberOfWickets = 0;
        averageEconomy = 0;
    }
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
    if (w < 0){
        throw string("Invalid Arguement: Number of wickets can't be negative\n");
    }
    else{
        numberOfWickets += w;
        increamentMatches();
        averageEconomy = (float)(numberOfWickets) / numberOfMatchesPlayed;
    }
}

class Alrounder : public Batsman, public Bowler{
    using Batsman::addRun;
    using Bowler::addWicket;
public:
    Alrounder(char* name, char* date) :Batsman(name, date), Bowler(name, date), Cricketer(name, date){}
    //Overrides the base class virtual function to display additional info with those in base class
    void displayInfo();

    //Update run and wicket together of a single match
    void updateRunWicket(int run, int wicket){
        addRun(run);
        numberOfMatchesPlayed--;
        addWicket(wicket);
    }

};

void Alrounder::displayInfo(){
    Batsman::displayInfo();
    cout << "Total Wickets: " << numberOfWickets << endl;
    cout << "Average Economy: " << averageEconomy << endl;
}

class DoubleWicketPair{
    Batsman batsman;
    Bowler bowler;

public:
    DoubleWicketPair(Batsman bt, Bowler bl) :batsman(bt), bowler(bl){}
    void displayInfo();
};

void DoubleWicketPair::displayInfo(){
    cout << "Batsman:" << endl;
    batsman.displayInfo();
    cout << "\nBowler:" << endl;
    bowler.displayInfo();
}

int main(){
    char btName[] = "Sachin Tendulkar"; char btDOB[] = "12/02/1960";
    char blName[] = "Zahir Khan"; char blDOB[] = "12/02/1960";
    char alName[] = "Yubraj Singh"; char alDOB[] = "12/02/1960";

    Batsman batsman(btName,btDOB);
    Bowler bowler(blName,blDOB);
    Alrounder alrounder(alName,alDOB);
    DoubleWicketPair pair(batsman,bowler);

    cout<<"Batsman:\n";batsman.displayInfo();cout<<"\n";
    cout << "Boler:\n";bowler.displayInfo();cout << "\n";
    cout << "Alrounder:\n";alrounder.displayInfo();cout << "\n";
    cout << "Double Wicket Pair:\n";pair.displayInfo();cout << "\n";

    cout<<"Let's add run to batsman:\n";
    for(int i=0;i<5;i++){
        int run;
        cout<<"Add run of a match:";cin>>run;
        batsman.addRun(run);
    }
    cout<<"Updated Info of batsman:\n";
    batsman.displayInfo();

    cout << "Let's add run to bowler:\n";
    for (int i = 0;i < 5;i++){
        int w;
        cout << "Add wicket of a match:";cin >> w;
        bowler.addWicket(w);
    }
    cout << "Updated Info of bowler:\n";
    bowler.displayInfo();

    cout << "Let's add run to alrounder:\n";
    for (int i = 0;i < 5;i++){
        int run;int wicket;
        cout << "Add run of a match:";cin >> run;
        cout<<"Add wicket of same match:";cin>>wicket;
        alrounder.updateRunWicket(run,wicket);
    }
    cout << "Updated Info of alrounder:\n";
    alrounder.displayInfo();
}
