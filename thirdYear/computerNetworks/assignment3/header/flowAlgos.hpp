#include "networknode.hpp"
#include "delay.hpp"
#include<thread>
#include<mutex>

#define TRIP_COUNT 30
#define SENDER_PORT 8000
// #define CHANNEL_PORT 8080
#define RS_GAP 180


class PairedNode_1P{
    ComputerNode channel;
    bool isChannelIdle;

    std::mutex mut;
public:
    PairedNode_1P() :channel(CHANNEL_PORT, false, 1){
        isChannelIdle = true;
    }

    vector<char> getData(int senderPort, int seq){
        DataHeader h = makeHeader(senderPort, senderPort + RS_GAP, seq);
        vector<char> data;
        data.resize(sizeof(h));
        memcpy(data.data(), (char*)&h, sizeof(h));
        return data;
    }

    void senderProgramme(const int senderPort){
        ComputerNode senderNode(senderPort, false, 1);
        cout << "Sender programme starts\n";

        int count = 0, loopCount = 0;

        while (count < TRIP_COUNT){
            bool canSend = false;
            {
                std::lock_guard<std::mutex> lk(mut);
                if (isChannelIdle){
                    isChannelIdle = false;
                    canSend = true;
                }
            }
            if (canSend){
                vector<char> data = getData(senderPort, count);
                bool flag = senderNode.sendData(data);
                if (flag) count++;
            }else{
                randomDelay();
            }
            loopCount++;
            cout << senderPort << ":Sender side  Count: " << count << " Loop count: " << loopCount << endl;

        }
        cout << "sender:" << senderPort << " Process finished\n";
    }

    void recieverProgramme(const int recieverPort){
        ComputerNode recieverNode(recieverPort, true, 1);
        cout << "Reciever programme starts:\n";
        int count = 0;
        vector<char> data;
        data.resize(sizeof(DataHeader));
        long long startTime = getCurrentTimestamp(); //micro second

        while (count < TRIP_COUNT){
            recieverNode.recieveData(data);
            {
                std::lock_guard<std::mutex> lk(mut);
                isChannelIdle = true;
            }
            cout << recieverPort << ":reciever count: " << count++ << endl;
            long long endTime = getCurrentTimestamp();
            cout << "Frame rate: " << (count * 1000000) / ((double)(endTime - startTime)) << " per second\n";
        }

        cout << recieverPort << ":Reciever process finished\n";
    }

    void channelProgramme(){
        while (true){
            vector<char> rawData;
            int status = channel.recieveData(rawData, true);
            if (status > 0){
                channel.sendData(rawData, false);
            }
        }
    }

    void run(){
        int n;
        cout << "number of node pairs: ";
        cin >> n;
        vector<thread> thd;
        thread channel(&PairedNode_1P::channelProgramme, this);
        for (int i = 0;i < n;i++){
            thread tsend(&PairedNode_1P::senderProgramme, this, SENDER_PORT + i);
            thread trecieve(&PairedNode_1P::recieverProgramme, this, SENDER_PORT + RS_GAP + i);

            thd.push_back(move(tsend));
            thd.push_back(move(trecieve));
        }

        for (auto& t : thd){
            t.join();
        }
        channel.join();
    }
};




class PairedNode_NonP{
    ComputerNode channel;
    bool isChannelIdle;

    std::mutex mut;
public:
    PairedNode_NonP() :channel(CHANNEL_PORT, false, 1){
        isChannelIdle = true;
    }

    vector<char> getData(int senderPort, int seq){
        DataHeader h = makeHeader(senderPort, senderPort + RS_GAP, seq);
        vector<char> data;
        data.resize(sizeof(h));
        memcpy(data.data(), (char*)&h, sizeof(h));
        return data;
    }

    void senderProgramme(const int senderPort){
        ComputerNode senderNode(senderPort, false, 1);
        cout << "Sender programme starts\n";

        int count = 0, loopCount = 0;

        while (count < TRIP_COUNT){
            bool canSend = false;
            {
                std::lock_guard<std::mutex> lk(mut);
                if (isChannelIdle){
                    isChannelIdle = false;
                    canSend = true;
                }
            }
            if (canSend){
                vector<char> data = getData(senderPort, count);
                bool flag = senderNode.sendData(data);
                if (flag) count++;
            }
            else{
                randomDelay();
            }
            loopCount++;
            cout << senderPort << ":Sender side  Count: " << count << " Loop count: " << loopCount << endl;

        }
        cout << "sender:" << senderPort << " Process finished\n";
    }

    void recieverProgramme(const int recieverPort){
        ComputerNode recieverNode(recieverPort, true, 1);
        cout << "Reciever programme starts:\n";
        int count = 0;
        vector<char> data;
        data.resize(sizeof(DataHeader));
        long long startTime = getCurrentTimestamp(); //micro second

        while (count < TRIP_COUNT){
            recieverNode.recieveData(data);
            {
                std::lock_guard<std::mutex> lk(mut);
                isChannelIdle = true;
            }
            cout << recieverPort << ":reciever count: " << count++ << endl;
            long long endTime = getCurrentTimestamp();
            cout << "Frame rate: " << (count * 1000000) / ((double)(endTime - startTime)) << " per second\n";
        }

        cout << recieverPort << ":Reciever process finished\n";
    }

    void channelProgramme(){
        while (true){
            vector<char> rawData;
            int status = channel.recieveData(rawData, true);
            if (status > 0){
                channel.sendData(rawData, false);
            }
        }
    }

    void run(){
        int n;
        cout << "number of node pairs: ";
        cin >> n;
        vector<thread> thd;
        thread channel(&PairedNode_NonP::channelProgramme, this);
        for (int i = 0;i < n;i++){
            thread tsend(&PairedNode_NonP::senderProgramme, this, SENDER_PORT + i);
            thread trecieve(&PairedNode_NonP::recieverProgramme, this, SENDER_PORT + RS_GAP + i);

            thd.push_back(move(tsend));
            thd.push_back(move(trecieve));
        }

        for (auto& t : thd){
            t.join();
        }
        channel.join();
    }
};


class PairedNode_PPersistent{
    ComputerNode channel;
    bool isChannelIdle;

    std::mutex mut;
public:
    PairedNode_PPersistent() :channel(CHANNEL_PORT, false, 1){
        isChannelIdle = true;
    }

    vector<char> getData(int senderPort, int seq){
        DataHeader h = makeHeader(senderPort, senderPort + RS_GAP, seq);
        vector<char> data;
        data.resize(sizeof(h));
        memcpy(data.data(), (char*)&h, sizeof(h));
        return data;
    }

    void senderProgramme(const int senderPort){
        ComputerNode senderNode(senderPort, false, 1);
        cout << "Sender programme starts\n";

        int count = 0, loopCount = 0;

        while (count < TRIP_COUNT){
            bool canSend = false;
            {
                std::lock_guard<std::mutex> lk(mut);
                if (isChannelIdle){
                    isChannelIdle = false;
                    canSend = true;
                }
            }
            if (canSend){
                vector<char> data = getData(senderPort, count);
                bool flag = senderNode.sendData(data);
                if (flag) count++;
            }
            else{
                randomDelay();
            }
            loopCount++;
            cout << senderPort << ":Sender side  Count: " << count << " Loop count: " << loopCount << endl;

        }
        cout << "sender:" << senderPort << " Process finished\n";
    }

    void recieverProgramme(const int recieverPort){
        ComputerNode recieverNode(recieverPort, true, 1);
        cout << "Reciever programme starts:\n";
        int count = 0;
        vector<char> data;
        data.resize(sizeof(DataHeader));
        long long startTime = getCurrentTimestamp(); //micro second

        while (count < TRIP_COUNT){
            recieverNode.recieveData(data);
            {
                std::lock_guard<std::mutex> lk(mut);
                isChannelIdle = true;
            }
            cout << recieverPort << ":reciever count: " << count++ << endl;
            long long endTime = getCurrentTimestamp();
            cout << "Frame rate: " << (count * 1000000) / ((double)(endTime - startTime)) << " per second\n";
        }

        cout << recieverPort << ":Reciever process finished\n";
    }

    void channelProgramme(){
        while (true){
            vector<char> rawData;
            int status = channel.recieveData(rawData, true);
            if (status > 0){
                channel.sendData(rawData, false);
            }
        }
    }

    void run(){
        int n;
        cout << "number of node pairs: ";
        cin >> n;
        vector<thread> thd;
        thread channel(&PairedNode_PPersistent::channelProgramme, this);
        for (int i = 0;i < n;i++){
            thread tsend(&PairedNode_PPersistent::senderProgramme, this, SENDER_PORT + i);
            thread trecieve(&PairedNode_PPersistent::recieverProgramme, this, SENDER_PORT + RS_GAP + i);

            thd.push_back(move(tsend));
            thd.push_back(move(trecieve));
        }

        for (auto& t : thd){
            t.join();
        }
        channel.join();
    }
};



