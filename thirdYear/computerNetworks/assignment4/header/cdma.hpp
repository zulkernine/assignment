#include "networknode.hpp"
#include<thread>
#include<mutex>


using namespace std;

class CDMA_FLOW{
    vector<vector<int>> walshCalculationBoard;
    vector<vector<int>> walshTable;
    int stationCounts;

public:
    CDMA_FLOW(int stationCounts):walshCalculationBoard(stationCounts, vector<int>(stationCounts, 0)),
        walshTable(stationCounts, vector<int>(stationCounts, 0)), stationCounts(stationCounts)
    {
        generateWalshTable(stationCounts, 0, stationCounts - 1, 0,
            stationCounts - 1, false);

        showWalshTable(stationCounts);
    }

    vector<int> encodeData(vector<int> data){
        for (int i = 0; i < stationCounts; i++){
            for (int j = 0; j < stationCounts; j++){
                walshCalculationBoard[i][j] = walshTable[i][j] * data[i];
            }
        }

        vector<int> channelData = vector<int>(stationCounts, 0);

        for (int i = 0; i < stationCounts; i++) 
            for (int j = 0; j < stationCounts; j++) 
                channelData[i] += walshCalculationBoard[j][i];
        
        return channelData;
    }

    int getDataOfStation(int sourceStationId,vector<int> channelData){
        int innerProduct = 0;

        for (int i = 0; i < stationCounts; i++) {
            innerProduct += walshTable[sourceStationId][i] * channelData[i];
        }

        return (innerProduct / stationCounts);
    }


    int generateWalshTable(int len, int i1, int i2, int j1,
        int j2, bool isBar)
    {
        if (len == 2) {

            if (!isBar) {

                walshTable[i1][j1] = 1;
                walshTable[i1][j2] = 1;
                walshTable[i2][j1] = 1;
                walshTable[i2][j2] = -1;
            }
            else {
                walshTable[i1][j1] = -1;
                walshTable[i1][j2] = -1;
                walshTable[i2][j1] = -1;
                walshTable[i2][j2] = +1;
            }

            return 0;
        }

        int midi = (i1 + i2) / 2;
        int midj = (j1 + j2) / 2;

        generateWalshTable(len / 2, i1, midi, j1, midj, isBar);
        generateWalshTable(len / 2, i1, midi, midj + 1, j2, isBar);
        generateWalshTable(len / 2, midi + 1, i2, j1, midj, isBar);
        generateWalshTable(len / 2, midi + 1, i2, midj + 1, j2, !isBar);

        return 0;
    }

    void showWalshTable(int stationCounts)
    {

        cout<<"\n";

        for (int i = 0; i < stationCounts; i++) {
            for (int j = 0; j < stationCounts; j++) {
                cout << walshTable[i][j] << " ";
            }
            cout<<endl;
        }
        cout<<"-------------------------\n";
        cout<<endl;
    }

    // Driver Code
    // static void main(String[] args)
    // {
    //     int stationCounts = 4;

    //     int[] data = new int[stationCounts];

    //     //data bits corresponding to each station
    //     data[0] = -1;
    //     data[1] = -1;
    //     data[2] = 0;
    //     data[3] = 1;

    //     CDMA channel = new CDMA();

    //     channel.setUp(data, stationCounts);

    //     // station you want to listen to
    //     int sourceStation = 3;

    //     channel.listenTo(sourceStation, stationCounts);
    // }
};
