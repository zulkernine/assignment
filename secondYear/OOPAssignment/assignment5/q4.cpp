/*
    Each cricketer has name, date of birth and matches played. Cricketer may be a bowler or batsman.
    
    For a bowler, number of wickets taken, average economy is stored.
    
    For a batsman, total runs scored,average score is stored.
    
    A double wicket pair is formed taking a bowler and a batsman.
    
    An all-rounder is both a bowler and batsman.
    
    Support must be there to show the details of a cricketer, bowler, batsmen,
    all-rounder and the pair.
*/

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
    void increamentMatches();
};

class Batsman: virtual public Cricketer{
protected:
    int totalRuns;
    float averageRun;

public:
    //Overrides the base class virtual function to display additional info with those in base class
    void displayInfo();

    //Add to total run
    void addRun(int newRun);
};

class Bowler: virtual public Cricketer{
protected:
    int numberOfWickets;
    float averageEconomy;
public:
    //Overrides the base class virtual function to display additional info with those in base class
    void displayInfo();

    //Add to total wicket
    void addWicket(int newWicket);
};

class Alrounder: public Batsman,public Bowler{
public:
    //Overrides the base class virtual function to display additional info with those in base class
    void displayInfo();
};

class DoubleWicketPair{
    Batsman batsman;
    Bowler bowler;

public:
    DoubleWicketPair(Batsman bt,Bowler bl);
    void displayInfo();
};
