#include "../header/flowcontrol.hpp"
#include <errno.h>

#define MY_PORT 8082    //Current node port number
#define DEST_PORT 8081    //Destination node port number
#define TIMEOUT 20000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 2

using namespace std;

class StopNWaitReciever : public RecieverNodeFlow{
    int sn;
    bool eventRequestToRecieve;

    //Performance purpose
    long long initialTime = 0, totalDataRecived = 0;


public:
    StopNWaitReciever(int my_port_num, int dest_port, string dataFileName) :RecieverNodeFlow(my_port_num, dest_port, dataFileName){
        sn = 0;
        eventRequestToRecieve = true;
    }

    void run(){
        sn = 0;
        long long j = 0;
        while (eventRequestToRecieve){
            cout << "Iteration count: " << (j++) << endl;
            cout << "err: " << errno << endl;

            int i = recvFrame(true);
            if (!initialTime) initialTime = getCurrentTimestamp();
            if (i > 0) totalDataRecived += i;

            if (i >= 0 && !CRC::hasError(frame)){
                cout << "Recieve status: " << i << endl;
                // if (CRC::hasError(frame)) continue;

                DataHeader h;
                extractData(h);
                if (h.seqNo == sn){
                    deliverData();
                    sn = (sn + 1) % MODULO;
                }

                sendFrame(sn);
                if (h.type == COMPLETION_ACK){
                    eventRequestToRecieve = false;

                    long long t = getCurrentTimestamp();
                    cout << "Reciever thoroughput: " << ((double)totalDataRecived / (t - initialTime)) << endl;
                }
            }

        }
    }

};


void protected_main(){
    string fileName;
    cout << "Output file name: ";
    cin >> fileName;

    StopNWaitReciever recieverNode(MY_PORT, DEST_PORT, fileName);
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
