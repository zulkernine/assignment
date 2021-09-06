#include "../header/flowcontrol.hpp"
#include <errno.h>
#include <unordered_map>

#define MY_PORT 8084    //Current node port number
#define DEST_PORT 8083    //Destination node port number
#define TIMEOUT 20000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 16   // m=4,     

using namespace std;

class SelectiveRepeatReciever : public RecieverNodeFlow{
    int sn;
    bool eventRequestToRecieve;
    bool nackSent;
    bool ackNeed;

    unordered_map<int, vector<char>> frameWindow;

    //Performance purpose
    long long initialTime = 0, totalDataRecived = 0;

    bool withinWindow(int n){
        const int sw = MODULO / 2;
        if (sw + sn - 1 < MODULO){
            return (sn <= n && n < (sn + sw));
        }
        else{
            return (sn <= n && n < MODULO) || (0 <= n && n < ((sn + sw) % MODULO));
        }
    }

    int deliverData(int n){
        if (transferComplete){
            ouputData.close();
            return -1;
        }
        else
            ouputData.write(frameWindow[n].data(), frameWindow[n].size() * sizeof(char));
        return 1;
    }

public:
    SelectiveRepeatReciever(int my_port_num, int dest_port, string dataFileName) :RecieverNodeFlow(my_port_num, dest_port, dataFileName){
        sn = 0;
        eventRequestToRecieve = true;
    }

    void run(){
        sn = 0;
        long long j = 0;
        nackSent = false;
        ackNeed = false;
        frameWindow.clear();

        while (eventRequestToRecieve){
            cout << "Iteration count: " << (j++) << endl;

            int i = recvFrame(true);


            if (!initialTime) initialTime = getCurrentTimestamp();
            if (i > 0) totalDataRecived += i;

            bool corruptedFrame = CRC::hasError(frame);

            if (i >= 0 && corruptedFrame){
                sendFrame(sn, true); //send NACK
                nackSent = true;
                continue;
            }

            if (i >= 0 && !corruptedFrame){

                DataHeader h;
                extractData(h);
                cout << "Recieved seq: " << h.seqNo << endl;

                if (h.seqNo != sn){
                    sendFrame(sn, true); //sendNAck
                }

                if (withinWindow(h.seqNo) && frameWindow.find(h.seqNo) == frameWindow.end()){
                    frameWindow[h.seqNo] = data; //store and mark the seqNo

                    while (frameWindow.find(sn) != frameWindow.end()){
                        deliverData(sn);
                        frameWindow.erase(sn);
                        sn = (sn + 1) % MODULO;
                        ackNeed = true;
                    }

                    if (ackNeed){
                        sendFrame(sn);
                        ackNeed = false;
                        nackSent = false;
                    }

                    if (h.type == COMPLETION_ACK){
                        eventRequestToRecieve = false;
                        cout << "COMPLETEION_ACK recieved, terminationg the program\n";

                        long long t = getCurrentTimestamp();
                        cout << "Reciever thoroughput: " << ((double)totalDataRecived / (t - initialTime)) << endl;
                    }
                }
            }

        }
    }

};


void protected_main(){
    string fileName;
    cout << "Output file name: ";
    cin >> fileName;

    SelectiveRepeatReciever recieverNode(MY_PORT, DEST_PORT, fileName);
    recieverNode.run();
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
