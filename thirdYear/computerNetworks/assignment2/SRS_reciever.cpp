#include "../header/flowcontrol.hpp"
#include <errno.h>

#define MY_PORT 8082    //Current node port number
#define DEST_PORT 8081    //Destination node port number
#define TIMEOUT 1000000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits
#define MODULO 16   // m=4,     

using namespace std;

class GoBackNReciever : public RecieverNodeFlow{
    int sn;
    bool eventRequestToRecieve;


public:
    GoBackNReciever(int my_port_num, int dest_port, string dataFileName) :RecieverNodeFlow(my_port_num, dest_port, dataFileName){
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
            if (i >= 0 && !CRC::hasError(frame)){
                cout << "Recieve status: " << i << endl;
                // if (CRC::hasError(frame)) continue;

                DataHeader h;
                extractData(h);
                cout << "Recieved seq: " << h.seqNo << endl;

                if (h.seqNo == (sn % MODULO)){
                    deliverData();
                    sn = (sn + 1);
                }

                sendFrame(sn % MODULO);  //send acknowledgement
                cout << "sneding ack: " << sn << " - " << (sn % MODULO) << endl;
                if (h.type == COMPLETION_ACK){
                    eventRequestToRecieve = false;
                    cout << "COMPLETEION_ACK recieved, terminationg the program\n";
                }
            }

        }
    }

};


void protected_main(){
    string fileName;
    cout << "Output file name: ";
    cin >> fileName;

    GoBackNReciever recieverNode(MY_PORT, DEST_PORT, fileName);
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
