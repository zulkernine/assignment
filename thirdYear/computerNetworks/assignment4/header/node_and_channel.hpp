#include<iostream>
#include "cdma.hpp"
#include<random>

using namespace std;


#define RS_GAP 4
#define DATA_SIZE 8

random_device generator;

string randomData(int delay = -1){
    string bin="";
    for(int i=0;i<DATA_SIZE;i++){
        bin += (generator()%2 + '0');
    }

    return bin;
}

class Station{
    const int stationId;
    string data;

public:
    Station(int index,bool willRecieve):stationId(index){
        if(willRecieve) data="";
        else
            data = randomData();
    }

    int getData(){
        if (data.length() > 0){
            int r;
            if (data[0] == '0') r = -1;
            else r = 1;

            data = data.substr(1);
            return r;
        }
        else return 0;
    }

    void recieveData(CDMA_FLOW& cdma, vector<int> encodedData){
        int ch = cdma.getDataOfStation(stationId - RS_GAP, encodedData);
        if(ch>0) data+='1';
        else if(ch<0) data += '0';
        else data+='N';

        cout<<"StationId: "<<stationId<<"\t recieved,total: "<<data<<"\n";
    }

};
