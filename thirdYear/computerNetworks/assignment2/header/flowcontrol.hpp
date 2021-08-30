#include "networknode.hpp"
#include "errorDetection.hpp"
#include <fstream>
#include <sys/time.h>
#include <unordered_map>
#include "error_delay.hpp"

#define DATA_LENGTH 64  //Byte or 512bits

using namespace std;


class SenderNodeFlow{

protected:
    const int destPort;
    const int myPort;
    ComputerNode currentNode;
    vector<char> data;
    vector<char> frame;
    vector<char> ackFrame;
    unordered_map<int, vector<char>> storage;
    ifstream inputData;
    bool transferComplete;
    bool makingNewFrameComplete;

    long long int getCurrentTimestamp(){
        struct timeval tp;
        gettimeofday(&tp, NULL);
        long long int micros = tp.tv_sec * 1000000 + tp.tv_usec;
        return micros;
    }
    
    int getData(){
        if (!inputData.eof()){
            data.resize(DATA_LENGTH);
            inputData.read(data.data(), DATA_LENGTH * sizeof(char));
            if (inputData.eof()){
                data.resize(inputData.gcount());
            }
            return 0;
        }
        else{
            transferComplete = true;
            data.resize(0);
            inputData.close();
            return -1;
        }
    }

    void makeFrame(int sn){
        vector<char> temp_data(sizeof(DataHeader) + data.size() * sizeof(char),0);
        if(transferComplete){
            DataHeader head = makeHeader(myPort, destPort, 0, COMPLETION_ACK, sn);

            memcpy(temp_data.data(), (char*)&head, sizeof(DataHeader));

            frame = CRC::encodeData(temp_data);
            makingNewFrameComplete=true;
        }else{
            DataHeader head = makeHeader(myPort, destPort, data.size(), RAW_DATA, sn);

            memcpy(temp_data.data(), (char*)&head, sizeof(DataHeader));
            memcpy(temp_data.data() + sizeof(DataHeader), data.data(), data.size() * sizeof(char));

            frame = CRC::encodeData(temp_data);
        }
    }

    void storeFrame(int sn){
        storage[sn] = frame;
    }
    void purgeFrame(int n){
        storage.erase(n);
    }

    void sendFrame(int sn){
        randomDelay();
        currentNode.sendData(storage[sn]);
    }

    int recvFrame(bool blocking = false){
        int status = currentNode.recieveData(ackFrame,blocking);
        return status;
    }

    int extractAck(DataHeader &h){
        if(CRC::hasError(ackFrame)){
            return -1;
        }

        memcpy(&h,ackFrame.data(),sizeof(DataHeader));
        return h.seqNo;
    }

public:
    SenderNodeFlow(int my_port_num, int dest_port, string dataFileName) :currentNode(my_port_num), myPort(my_port_num), destPort(dest_port){
        inputData.open(dataFileName,ios::in  | ios::binary);
        data.resize(DATA_LENGTH);
        transferComplete = false;
        makingNewFrameComplete = false;
    }

    virtual void run() = 0;

};

class RecieverNodeFlow{

protected:
    const int destPort;
    const int myPort;
    ComputerNode currentNode;
    vector<char> data;
    vector<char> frame;
    vector<char> ackFrame;
    bool transferComplete;
    ofstream ouputData;

    int deliverData(){
        if(transferComplete){
            ouputData.close();
            return -1;
        }
        else
            ouputData.write(data.data(), data.size() * sizeof(char));
        return 1;       
    }

    void makeAckFrame(long long sn,bool isNack){
        vector<char> temp_data;
        temp_data.resize(sizeof(DataHeader) + (transferComplete ? 0 : sizeof(sn)));
        DataHeader head = makeHeader(myPort, destPort, transferComplete ? 0 : sizeof(sn), transferComplete ? COMPLETION_ACK : (isNack ? NCK : ACK), sn);

        memcpy(temp_data.data(), (char*)&head, sizeof(DataHeader));
        if(!transferComplete) memcpy(temp_data.data() + sizeof(DataHeader), (char*)&sn, sizeof(sn));

        ackFrame = CRC::encodeData(temp_data);
    }

    void sendFrame(long long sn,bool isNack=false){
        randomDelay();
        makeAckFrame(sn, isNack);
        currentNode.sendData(ackFrame);
    }

    int recvFrame(bool blocking=false){
        int status = currentNode.recieveData(frame,blocking);
        return status;
    }

    int extractData(DataHeader &h){
        memcpy(&h,frame.data(),sizeof(h));
        data.resize(h.length - 32);
        memcpy(data.data(),frame.data()+sizeof(h),data.size());
        transferComplete = (h.type == COMPLETION_ACK);
        return (h.type == COMPLETION_ACK);
    }

public:
    RecieverNodeFlow(int my_port_num, int dest_port, string dataFileName) :currentNode(my_port_num), myPort(my_port_num), destPort(dest_port){
        data.resize(DATA_LENGTH);
        transferComplete = false;
        ouputData.open(dataFileName,ios::out|ios::binary);
    }

    virtual void run() = 0;
};

// class IntermediateChannel{

// }
