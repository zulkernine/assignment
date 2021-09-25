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


void randomDelay(){
    long long r = generator();
    int delay;
    delay = 1000 + r % 5000;
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}
