#include "../header/flowcontrol.hpp"
#include<thread>
#include<mutex>
#include<condition_variable>
#include <chrono>

#define MY_PORT 8081    //Current node port number
#define DEST_PORT 8082    //Destination node port number
#define TIMEOUT 1000000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 2

using namespace std;

class StopNWaitSender : public SenderNodeFlow{
    int sn;
    bool canSend;
    long long int timerTimeStamp;
    bool eventRequestToSend;

    int totalConsecutiveTimeout;

    std::mutex mut;
    std::condition_variable data_cond;

    void startTimer(){
        timerTimeStamp = getCurrentTimestamp();
    }
    void stopTimer(){
        timerTimeStamp = 0;
    }
    bool isTimeOut(){
        return (getCurrentTimestamp() > (timerTimeStamp + TIMEOUT));
    }

public:
    StopNWaitSender(int my_port_num, int dest_port, string dataFileName) :SenderNodeFlow(my_port_num, dest_port, dataFileName){
        sn = 0;
        canSend = false;
        eventRequestToSend = true;
    }

    void sendNewFrame(){
        while(true){
            std::unique_lock<std::mutex> lk(mut);
            if(!eventRequestToSend){
                cout<<"Seccessfully transmitted!\n";
                exit(0);
            }

            data_cond.wait(
                lk, [this]{return (eventRequestToSend && canSend);});
            
            getData();
            makeFrame(sn);
            storeFrame(sn);
            sendFrame(sn);
            startTimer();
            sn = (sn + 1) % MODULO;
            canSend = false;

            totalConsecutiveTimeout = 0;
            
            lk.unlock();
        }
    }

    void recieveAck(){
        while(true){
            if (!eventRequestToSend){
                cout << "Seccessfully transmitted!\n";
                exit(0);
            }

            if (recvFrame(true) > 0){
                totalConsecutiveTimeout = 0;
                DataHeader h;
                int status = extractAck(h);

                //Frame not corrupted and ack==Sn
                if (status == sn){
                    {
                        std::lock_guard<std::mutex> lk(mut);
                        stopTimer();
                        purgeFrame((sn - 1 + MODULO) % MODULO);
                        canSend = true;
                        if (h.type == COMPLETION_ACK){
                            eventRequestToSend = false;
                        }
                    }
                    data_cond.notify_one();
                }
            }


        }
    }

    void handleTimeOut(){
        while(true){
            std::lock_guard<std::mutex> lk(mut);

            if (isTimeOut()){
                startTimer();
                sendFrame((sn - 1 + MODULO) % MODULO);
                totalConsecutiveTimeout++;

                if (totalConsecutiveTimeout > 30){
                    cout << "Failed to recieve response 30 times consecutively!\nAborting programm!\n";
                    exit(1);
                }

                std::this_thread::sleep_for(75ms);
            }
        }
    }

    void run(){
        sn = 0;
        canSend = true;
        totalConsecutiveTimeout = 0;

        thread tsend(&StopNWaitSender::sendNewFrame, this);
        thread trecieve(&StopNWaitSender::recieveAck,this);
        thread ttimeout(&StopNWaitSender::handleTimeOut,this);

        tsend.join();
        trecieve.join();
        ttimeout.join();

    }

};


void protected_main(){
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;

    StopNWaitSender senderNode(MY_PORT, DEST_PORT, fileName);
    senderNode.run();
}

int main(){
    try{
        protected_main();
    }
    catch (string e){
        cout << e << "\n";
    }
    catch (exception e){
        cout << e.what() << "\n";
    }
}
