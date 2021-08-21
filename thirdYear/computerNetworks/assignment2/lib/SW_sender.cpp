#include "../header/networknode.hpp"
#include "../header/errorDetection.hpp"
#include "../header/flowcontrol.hpp"
#include <fstream>
#include <sys/time.h>
#include <unordered_map>

#define MY_PORT 8081    //Current node port number
#define TIMEOUT 1000000 //micro second
#define DATA_LENGTH 64  //Byte or 512bits

using namespace std;

class StopNWaitSender : public SenderNodeFlow{
    int sn;
    bool canSend;
    
public:
    StopNWaitSender(int my_port_num, int dest_port, string dataFileName):SenderNodeFlow(my_port_num,dest_port,dataFileName){
        sn = 0;
        canSend = false;
    }

    void run(){

    }

};


int protected_main(){

}

int main(){
    try{
        protected_main();
    }catch(string e){
        cout<<e<<"\n";
    }catch(exception e){
        cout<<e.what()<<"\n";
    }
}
