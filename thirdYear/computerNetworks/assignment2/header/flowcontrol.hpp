#include "../header/networknode.hpp"
#include "../header/errorDetection.hpp"
#include <fstream>
#include <sys/time.h>
#include <unordered_map>

#define TIMEOUT 1000000 //micro second
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
    long long int timerTimeStamp;
    ifstream inputData;

    long long int getCurrentTimestamp(){
        struct timeval tp;
        gettimeofday(&tp, NULL);
        long long int micros = tp.tv_sec * 1000000 + tp.tv_usec;
        return micros;
    }
    void startTimer(){
        timerTimeStamp = getCurrentTimestamp();
    }
    void stopTimer(){
        timerTimeStamp = 0;
    }
    bool isTimeOut(){
        return (getCurrentTimestamp() > (timerTimeStamp + TIMEOUT));
    }

    int getData(){
        if (!inputData.eof()){
            inputData.read(data.data(), DATA_LENGTH * sizeof(char));
            if (inputData.eof()){
                data.resize(inputData.gcount());
            }
            return 0;
        }
        else{
            return -1;
        }
    }

    void makeFrame(int sn){
        vector<char> temp_data(sizeof(DataHeader) + data.size() * sizeof(char));
        DataHeader head = makeHeader(myPort, destPort, data.size(),RAW_DATA,sn);

        memcpy(temp_data.data(), (char*)&head, sizeof(DataHeader));
        memcpy(temp_data.data() + sizeof(DataHeader), data.data(), data.size() * sizeof(char));

        frame = CRC::encodeData(temp_data);
    }

    void storeFrame(int sn){
        storage[sn] = frame;
    }
    void purgeFrame(int n){
        storage.erase(n);
    }

    void sendFrame(int sn){
        currentNode.sendData(storage[sn]);
    }

    int recvFrame(){
        int status = currentNode.recieveData(ackFrame);
        return status;
    }

public:
    SenderNodeFlow(int my_port_num, int dest_port, string dataFileName) :currentNode(my_port_num), myPort(my_port_num), destPort(dest_port){
        timerTimeStamp = 0;
        inputData.open(dataFileName);
        data.resize(DATA_LENGTH);
    }

    void run(){

    }

};

class RecieverNodeFlow{

protected:
    const int destPort;
    const int myPort;
    ComputerNode currentNode;
    vector<char> data;
    vector<char> frame;
    vector<char> ackFrame;
    unordered_map<int, vector<char>> storage;
    ofstream ouputData;

    int putData(){
        ouputData.write(data.data(), DATA_LENGTH * sizeof(char));
        
        
    }

    void makeFrame(int sn){
        vector<char> temp_data(sizeof(DataHeader) + data.size() * sizeof(char));
        DataHeader head = makeHeader(myPort, destPort, data.size(), RAW_DATA, sn);

        memcpy(temp_data.data(), (char*)&head, sizeof(DataHeader));
        memcpy(temp_data.data() + sizeof(DataHeader), data.data(), data.size() * sizeof(char));

        frame = CRC::encodeData(temp_data);
    }

    void storeFrame(int sn){
        storage[sn] = frame;
    }
    void purgeFrame(int n){
        storage.erase(n);
    }

    void sendFrame(int sn){
        currentNode.sendData(storage[sn]);
    }

    int recvFrame(){
        int status = currentNode.recieveData(ackFrame);
        return status;
    }

public:
    RecieverNodeFlow(int my_port_num, int dest_port, string dataFileName) :currentNode(my_port_num), myPort(my_port_num), destPort(dest_port){
        timerTimeStamp = 0;
        inputData.open(dataFileName);
        data.resize(DATA_LENGTH);
    }

    void run(){

    }
};
