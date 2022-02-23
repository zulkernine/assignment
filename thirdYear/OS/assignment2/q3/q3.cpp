#include<thread>
#include<iostream>
#include<chrono>
#include<semaphore.h>
#include<random>

#define LOOP_COUNT 25
using namespace std;

random_device generator;

sem_t readerSem,writerSem;

int readCount = 0;
int writeCount = 0;
long long DATA = 0;

long long getNewRandomData(){
    return generator();
}

void randomDelay(){
    int delay = generator()%500;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

class Reader {
public:
    void run() {
        for(int i=0;i<LOOP_COUNT;i++){
            cout<<"loop_count: "<<i<<endl;

            try {
                //Acquire Section
                sem_wait(&readerSem);
                readCount++;

                if (readCount == 1) {
                    sem_wait(&writerSem);
                }
                sem_post(&readerSem);

                //Reading section
                cout << "Current thread id: " << std::this_thread::get_id() << "\t is reading,count:" << readCount << "\tread data: " << DATA << "\n";
                
                cout << "Current thread id: " << std::this_thread::get_id() << "\t has completed reading\n\n";

                //Releasing section
                sem_wait(&readerSem);
                readCount--;
                if (readCount == 0) {
                    sem_post(&writerSem);
                }
                sem_post(&readerSem);

                randomDelay();
            }
            catch (exception e) {
                cout << e.what() << "\n";
                cout << "exception reader thread id: " << std::this_thread::get_id() << "\n";
            }
        }
        
    }
};

class Writer {
public:
    void run() {
        for(int i=0;i<LOOP_COUNT;i++){
            cout<<"writer loop count:"<<i<<endl;

            try {
                sem_wait(&writerSem);
                DATA = getNewRandomData();
                cout << "Current thread id: " << std::this_thread::get_id() << "\t is writing,count:" << (writeCount++) << "\t written data: " << DATA << "\n";

                // std::this_thread::sleep_for(WTST);
                cout << "Current thread id: " << std::this_thread::get_id() << "completed\n\n";
                sem_post(&writerSem);
                randomDelay();
            }
            catch (exception e) {
                cout << e.what() << "\n";
                cout << "exception writer thread id: " << std::this_thread::get_id() << "\n";
            }
        }
        
    }
};

int main() {
    sem_init(&readerSem, 0, 1);
    sem_init(&writerSem, 0, 1);

    Reader  reader;
    Writer writer;


    thread wt1(&Writer::run, &writer);
    thread rt1(&Reader::run, &reader);
    thread rt2(&Reader::run, &reader);
    thread wt2(&Writer::run, &writer);
    thread rt3(&Reader::run, &reader);
    
    rt1.join();
    rt2.join();
    rt3.join();
    wt1.join();
    wt2.join();

    cout<<"\n\n################ MAIN has exited  #############333333333########\n\n";
}

