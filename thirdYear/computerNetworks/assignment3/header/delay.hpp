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


void randomDelay(int delay = -1){
    if (delay < 0){
        long long r = generator();
        delay = r % 500;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

//Assumption p is between 0 and 1
bool p_probability_check(float p){
    int num = generator()%100;
    p *= 100;
    return (p>=num) ;
}

