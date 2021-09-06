#include "../header/flowcontrol.hpp"
#include<thread>
#include<mutex>
#include<condition_variable>
#include <chrono>

#define MY_PORT 8083   //Current node port number
#define DEST_PORT 8084    //Destination node port number
#define TIMEOUT 20000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 16   // m=4, 

using namespace std;

class SelectiveRepeatSender : public SenderNodeFlow{
    int sn;
    int sf;
    const int sw;
    bool eventRequestToSend;

    int totalConsecutiveTimeout;
    bool canSend;
    unordered_map<int, long long int> timerTimeStamp;
    // long long int timerTimeStamp;

    std::mutex mut;
    std::condition_variable data_cond;

    void startTimer(int n){
        timerTimeStamp[n] = getCurrentTimestamp();
    }
    void stopTimer(int n){
        timerTimeStamp.erase(n);
    }
    vector<int> isTimeOut(){
        vector<int> t;
        long long int curt = getCurrentTimestamp();

        for (auto p : timerTimeStamp){
            if (curt > (p.second + TIMEOUT * (MODULO/2)))
                t.push_back(p.first);
        }
        return t;
    }

public:
    SelectiveRepeatSender(int my_port_num, int dest_port, string dataFileName) :SenderNodeFlow(my_port_num, dest_port, dataFileName), sw(MODULO / 2){
        sn = 0;
        sf = 0;
        eventRequestToSend = true;
    }

    void sendNewFrame(){
        while (!makingNewFrameComplete){
            std::unique_lock<std::mutex> lk(mut);
            if (!eventRequestToSend){
                cout << "Seccessfully transmitted!\n";
                exit(0);
            }

            data_cond.wait(
                lk, [this]{return (eventRequestToSend && canSend);});

            getData();
            makeFrame(sn);
            storeFrame(sn);
            sendFrame(sn);
            startTimer(sn);
            sn = (sn + 1) % MODULO;

            if ((sn - sf == sw) || (MODULO - sf + sn) == sw){   // that is |sf-sn| == sw
                canSend = false;
            }

            totalConsecutiveTimeout = 0;

            lk.unlock();
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
                if (ackNo < 0) continue;//Corrupted frame

                if (h.type == NCK && storage.find(ackNo) != storage.end()){
                    std::lock_guard<std::mutex> lk(mut);
                    cout << "Recieved NCk: " << ackNo << endl;
                    sendFrame(ackNo);
                    startTimer(ackNo);
                    continue;
                }

                //Frame not corrupted and valid ack
                if (sf < ackNo && (ackNo <= sn || ackNo < (sf + sw))){
                    // if ((ackNo > (sf % MODULO)) && (ackNo <= (sn % MODULO))){
                    {
                        std::lock_guard<std::mutex> lk(mut);
                        cout << "Recieved__ ack: " << (ackNo) << "\n";

                        while (sf < ackNo){
                            cout << "Purging frame: " << (sf) << "\n";
                            purgeFrame(sf);
                            stopTimer(sf);
                            sf = (sf + 1) % MODULO;
                            if (sf == 0) break;
                        }

                        if (sn - sf < sw){
                            canSend = true;
                        }

                        if (h.type == COMPLETION_ACK){
                            eventRequestToSend = false;
                        }
                    }
                    data_cond.notify_one();
                }
                else if (ackNo <= sn && sf > sn){
                    // Reciver window slided to the next frame slot, therefore, ack < Sf
                    {
                        std::lock_guard<std::mutex> lk(mut);
                        cout << "Recieved__ ack: " << (ackNo) << "\n";

                        while (sf < MODULO){
                            cout << "Purging frame: " << (sf) << "\n";
                            purgeFrame(sf);
                            stopTimer(sf);
                            sf = (sf + 1) % MODULO;
                            if (sf == 0) break;
                        }

                        //Now sender window also arived at next slot
                        while (sf < ackNo){
                            cout << "Purging frame: " << (sf) << "\n";
                            purgeFrame(sf);
                            stopTimer(sf);
                            sf = (sf + 1) % MODULO;
                        }

                        if (sn - sf < sw){
                            canSend = true;
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
        while (eventRequestToSend){
            vector<int> tout = isTimeOut();
            for (int f : tout){
                std::lock_guard<std::mutex> lk(mut);
                startTimer(f);
                sendFrame(f);
                cout << "Re-Sending new frame, f:" << f << endl;
            }

            if (tout.size()) totalConsecutiveTimeout++;

            if (totalConsecutiveTimeout > 30){
                cout << "Failed to recieve response 30 times consecutively!\nAborting programm!\n";
                exit(1);
            }

            std::this_thread::sleep_for(50ms);
        }
    }

    void run(){
        sn = 0;
        sf = 0;
        totalConsecutiveTimeout = 0;

        thread ttimeout(&SelectiveRepeatSender::handleTimeOut, this);
        thread tsend(&SelectiveRepeatSender::sendNewFrame, this);
        thread trecieve(&SelectiveRepeatSender::recieveAck, this);

        tsend.join();
        trecieve.join();
        ttimeout.join();
    }

};


void protected_main(){
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;

    SelectiveRepeatSender senderNode(MY_PORT, DEST_PORT, fileName);
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
