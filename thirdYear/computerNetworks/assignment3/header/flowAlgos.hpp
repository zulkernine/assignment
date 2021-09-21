#include "networknode.hpp"
#define TRIP_COUNT 1000

class PairedNode_1P{
    const int senderPort;
    const int recieverPort;
    ComputerNode senderNode;
    ComputerNode recieverNode;

public:
    PairedNode_1P(int senderPort, int recieverPort):
    senderNode(senderPort,false,1),recieverNode(recieverPort,true,1),
    senderPort(senderPort),recieverPort(recieverPort)
    {

    }

    vector<char> getData(){
        DataHeader h = makeHeader(senderPort,recieverPort);
        vector<char> data;
        data.resize(sizeof(h));
        memcpy(data.data(),(char*)&h,sizeof(h));
    }

    void senderProgramme(){
        cout<<"Sender programme starts\n";

        int count=0,loopCount=0;
        vector<char> data = getData();
        

        while(count<TRIP_COUNT && loopCount < 3 * TRIP_COUNT){
            if(senderNode.isChannelIdle()){
                bool flag = senderNode.sendData(data);
                if(flag) count++;
            }
            loopCount++;
            cout<<"sender side  Count: "<<count<<" Loop count: "<<loopCount<<endl;

        }
        cout<<"Process finished\n";
    }

    void recieverProgramme(){
        cout<<"Reciever programme starts:\n";

        int count=0;
        vector<char> data;
        data.resize(sizeof(DataHeader));

        while(count<TRIP_COUNT){
            recieverNode.recieveData(data);
            cout<<"reciever count: "<<count++;
        }

        cout<<"Reciever process finished\n";
    }


    void run(){
        
    }
};
