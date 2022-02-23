#include "../header/networknode.hpp"
#include <thread>

#define MY_PORT 8080    //Channel port number

using namespace std;

ComputerNode channel(MY_PORT, false , 1);


void sendData(vector<char> rawData){
    // injectErrorRandom(rawData);
    channel.sendData(rawData, false);
}


int main(){
    while (true){
        vector<char> rawData;
        int status = channel.recieveData(rawData, true);
        if (status > 0){
            sendData(rawData);
        }
    }
}

