#include "../header/flowcontrol.hpp"
#include<thread>
#include<mutex>
#include<condition_variable>
#include <chrono>

#define MY_PORT 8081    //Current node port number
#define DEST_PORT 8082    //Destination node port number
#define TIMEOUT 20000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 16   // m=4, 

using namespace std;

class GoBackNSender : public SenderNodeFlow{
    int sn;
    int sf;
    const int sw;
    long long int timerTimeStamp;
    bool eventRequestToSend;

    int totalConsecutiveTimeout;
    bool canSend;

    std::mutex mut;
    std::condition_variable data_cond;

    void startTimer(){
        timerTimeStamp = getCurrentTimestamp();
    }
    void stopTimer(){
        timerTimeStamp = 0;
    }
    bool isTimeOut(){
        return (getCurrentTimestamp() > (timerTimeStamp + (long long)TIMEOUT * (sw / 2)));
    }

public:
    GoBackNSender(int my_port_num, int dest_port, string dataFileName) :SenderNodeFlow(my_port_num, dest_port, dataFileName), sw(MODULO - 1){
        sn = 0;
        sf = 0;
        eventRequestToSend = true;
    }

    void sendNewFrame(){
        while (true){
            std::unique_lock<std::mutex> lk(mut);
            if (!eventRequestToSend){
                cout << "Seccessfully transmitted!\n";
                exit(0);
            }

            data_cond.wait(
                lk, [this]{return (eventRequestToSend && canSend);});

            getData();
            makeFrame(sn % MODULO);
            storeFrame(sn % MODULO);
            sendFrame(sn % MODULO);
            sn = (sn + 1);
            startTimer();

            if(sn % MODULO == 0){
                canSend = false;
            }

            totalConsecutiveTimeout = 0;

            lk.unlock();
            cout << "Sending new frame, sf:" << sf << "  sn:" << sn << " sw:" << sw << "\n";
        }
    }

    void recieveAck(){
        while (true){

            if (!eventRequestToSend){
                cout << "Seccessfully transmitted!\n";
                exit(0);
            }

            if (recvFrame(true) > 0){
                totalConsecutiveTimeout = 0;
                DataHeader h;
                int ackNo = extractAck(h);

                if(ackNo <= -1) continue;//Corrupted frame

                cout << "Recieved ack: " << ackNo << "\n";

                //Frame not corrupted and valid ack
                if ((ackNo + sf) <= (sn)){
                    // if ((ackNo > (sf % MODULO)) && (ackNo <= (sn % MODULO))){
                    {
                        std::lock_guard<std::mutex> lk(mut);
                        cout << "sf: " << sf << "  " << MODULO << "   " << (sf % MODULO) << "\n";
                        cout << "Recieved__ ack: " << (ackNo) << "\n";
                        
                        while ((sf % MODULO) < ackNo){
                            cout << "Purging frame: " << (sf % MODULO) << " " << sf << "\n";
                            purgeFrame(sf % MODULO);
                            sf = (sf + 1);
                            stopTimer();
                        }

                        if (ackNo == 0 && storage.find(0) == storage.end()){ //Previous batch all acknowledged
                            canSend = true;
                            sf = sn;
                            storage.clear();
                        }

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
        while (true){

            {
                std::lock_guard<std::mutex> lk(mut);
                if (isTimeOut()){
                    cout << "timer stamp: " << timerTimeStamp << " " << getCurrentTimestamp() << endl;
                    startTimer();

                    int temp = sf;
                    while (temp < sn){
                        sendFrame(temp % MODULO);
                        temp = (temp + 1);
                        cout << "Re-Sending new frame, sf:" << sf << " sn:" << sn << endl;
                    }
                    totalConsecutiveTimeout++;

                    if (totalConsecutiveTimeout > 30){
                        cout << "Failed to recieve response 30 times consecutively!\nAborting programm!\n";
                        exit(1);
                    }

                }
            }

            std::this_thread::sleep_for(150ms);
        }
    }

    void run(){
        sn = 0;
        sf = 0;
        totalConsecutiveTimeout = 0;

        thread tsend(&GoBackNSender::sendNewFrame, this);
        thread trecieve(&GoBackNSender::recieveAck, this);
        thread ttimeout(&GoBackNSender::handleTimeOut, this);

        tsend.join();
        trecieve.join();
        ttimeout.join();

    }

};


void protected_main(){
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;

    GoBackNSender senderNode(MY_PORT, DEST_PORT, fileName);
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
