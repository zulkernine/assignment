#include<fstream>
#include<iostream>
#include<random>
#include<functional>

using namespace std;
random_device generator;

/* If random_device is not available, uncomment following code and comment above. */
// default_random_engine gen;
// uniform_int_distribution<int> distribution(0,1000);
// auto generator = bind(distribution, gen);

string injectError(string str){
    int len = str.length();
    int errNo = generator() % (len / 3);
    for (int i = 0;i < errNo;i++){
        int ind = generator() % len;
        if (str[ind] == '0') str[ind] = '1';
        else str[ind] = '0';
    }
    return str;
}

int main(){
    ifstream input("random_binary_stings.txt", ios::in);
    if (!input) {
        cout << "Cannot open file.\n";
        exit(1);
    }

    for (int i = 0;i < 100;i++){
        string str;
        input >> str;
        cout<<str<<"\n";
        cout <<injectError(str)<< "\n\n";
    }

    input.close();
    return 0;
}
