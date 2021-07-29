#include<fstream>
#include<iostream>
#include<random>
#include<functional>

using namespace std;

random_device generator;
// uniform_int_distribution<int> distribution(0,1);

// auto binary = bind(distribution, generator);

int main(){
    ofstream output("random_binary_stings.txt", ios::out);
    if (!output) {
        cout << "Cannot open file.\n";
        exit(1);
    }

    for(int i=0;i<100000;i++){
        for (int i = 0;i < 64;i++){
            output << generator()%2 ;
        }
        output << "\n";
    }

    output.close();
    return 0;
}
