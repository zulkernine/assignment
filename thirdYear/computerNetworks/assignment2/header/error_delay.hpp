#include<string>
#include<random>
#include<functional>
#include<chrono>
#include<thread>

#define ERROR_RATE 5 // 5 packets out of 100 will get erroneous

using namespace std;

random_device generator;

/* If random_device is not available, uncomment following code and comment above. */
// default_random_engine gen;
// uniform_int_distribution<int> distribution(0,1000);
// auto generator = bind(distribution, gen);

// Codeword should be minimum 12 character long
void injectErrorRandom(vector<char> &data){
    if(generator()%100 > ERROR_RATE) return;

    int len = data.size();
    int errNo = generator() % (len / 4 - 1) + 1;    //Minimum 1 bit flips
    
    for (int i = 0;i < errNo;i++){
        int ind = generator() % len;
        data[ind] ^= (1 << (generator()%sizeof(char)));
    }
}

void randomDelay(){
    long long r = generator();
    int delay;
    if(r % 300 == 1){
        delay = 10000 + r % 50000;
        std::this_thread::sleep_for(std::chrono::microseconds(delay));
    }else{
        delay = r%5000 ;
        std::this_thread::sleep_for(std::chrono::microseconds(delay));
    }
}
