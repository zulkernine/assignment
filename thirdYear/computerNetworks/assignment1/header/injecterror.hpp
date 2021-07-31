#include<string>
#include<random>
#include<functional>
#define DATAWORD_LENGTH 64

using namespace std;

random_device generator;

/* If random_device is not available, uncomment following code and comment above. */
// default_random_engine gen;
// uniform_int_distribution<int> distribution(0,1000);
// auto generator = bind(distribution, gen);

// Codeword should be minimum 12 character long
string injectErrorRandom(string str, int& bitFlips){
    int len = str.length();
    int errNo = generator() % (len / 3 - 1) + 1;    //Minimum 4 bit flips
    bitFlips = errNo;
    for (int i = 0;i < errNo;i++){
        int ind = generator() % len;
        if (str[ind] == '0') str[ind] = '1';
        else str[ind] = '0';
    }
    return str;
}

string newErrorPattern(int& bitFlips){
    string str = "";
    for (int i = 0;i < DATAWORD_LENGTH;i++) str += "0";

    int errNo = generator() % (DATAWORD_LENGTH / 3 - 1) + 1;    //Minimum 1 bit flips
    bitFlips = errNo;
    for (int i = 0;i < errNo;i++){
        int ind = generator() % DATAWORD_LENGTH;
        str[ind] = '1';
    }
    return str;
}

string injectErrorDataword(string str, string pattern){
    for (int i = 0;i < pattern.length();i++){
        //Bit flip
        if (pattern[i] == '1'){
            if (str[i] == '0') str[i] = '1';
            else str[i] = '0';
        }
    }
    return str;
}
