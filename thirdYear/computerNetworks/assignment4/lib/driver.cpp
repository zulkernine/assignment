#include "../header/node_and_channel.hpp"

int main(){
    int numberOfStations = RS_GAP*2;

    CDMA_FLOW cdma(numberOfStations);
    vector<Station> stations;
    for(int i=0;i<numberOfStations;i++){
        if(i<RS_GAP-1){
            stations.push_back(Station(i,false));
        }
        else stations.push_back(Station(i, true));
    }

    for(int i=0;i<DATA_SIZE;i++){
        vector<int> channelRawData;
        for(int i=0;i<RS_GAP;i++)
            channelRawData.push_back(stations[i].getData());
        
        vector<int> encodedData = cdma.encodeData(channelRawData);

        for(int i=RS_GAP;i<numberOfStations;i++)
            stations[i].recieveData(cdma,encodedData);
    }
}
