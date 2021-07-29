#include<string>
#include<random>
#include<functional>

using namespace std;

random_device generator;

/* If random_device is not available, uncomment following code and comment above. */
// default_random_engine gen;
// uniform_int_distribution<int> distribution(0,1000);
// auto generator = bind(distribution, gen);

// Codeword should be minimum 12 character long
string injectError(string str,int& bitFlips){
    int len = str.length();
    int errNo = generator() % (len/3 - 4) + 4;    //Minimum 4 bit flips
    bitFlips = errNo;
    for (int i = 0;i < errNo;i++){
        int ind = generator() % len;
        if (str[ind] == '0') str[ind] = '1';
        else str[ind] = '0';
    }
    return str;
}
