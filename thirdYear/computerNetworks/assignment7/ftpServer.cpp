#include "./header/node.hpp"
#include "./header/ftpProtocolConstant.hpp"
#include<fstream>

const string userName = "zulqarnain";
const string password = "abcd1234";

vector<char> getFileContent(string fileName){
    vector<char> raw;

    std::ifstream input(fileName, ios::in|ios::binary);
    if(!input) return raw;

    raw.resize(MAX_BUFFER_SIZE);
    
    input.read(raw.data(), MAX_BUFFER_SIZE);
    raw.resize(input.gcount());
    input.close();
    return raw;

}

class FTPServer{
    const string dataPath="./DATA/";
    ComputerNode self;
    ConnectionSocket clientControl; // for control connection
    ConnectionSocket dataConnection; // for data connection
    bool isAuthorized;

    string getAvailbleDataList(){
        system("ls DATA > temp.txt");

        std::ifstream inFile("temp.txt");

        std::stringstream strStream;
        strStream << inFile.rdbuf();
        return strStream.str(); 
    }

    UserInput getClientInput(){
        vector<char> raw;
        self.recieveData(raw,clientControl);
        UserInput inp;
        memcpy((char*)&inp,raw.data(),sizeof(inp));
        cout<<"Clinet: "<<inp.getCommand()<<"  "<<inp.getArg()<<"\n\n";

        return inp;
    }
    void sendStatus(int status){
        vector<char> raw;
        raw.resize(sizeof(status));
        memcpy(raw.data(),(char*)&status,sizeof(status));
        self.sendData(raw,clientControl);
    }
public:
    FTPServer(int port):self(port){
        cout<<"FTP server started\n";
        isAuthorized = false;
    }

    void run(){
        clientControl = ComputerNode::acceptConnection(self.getSelfListenerSocket());
        sendStatus(220);

        UserInput input;
        do{
            input = getClientInput();
            switch(input.getCommand()){
                case USER:{
                    int cmp = input.getArg().compare(userName);
                    if(cmp == 0){
                        sendStatus(331);
                    }else{
                        sendStatus(401);
                    }
                } break;

                case PASSWORD:{
                    if (input.getArg() == password){
                        isAuthorized = true;
                        sendStatus(230);
                    }
                    else{
                        sendStatus(401);
                    }
                } break;

                case PORT:{
                    if(!isAuthorized){
                        sendStatus(404);
                        break;
                    }

                    int p = stoi(input.getArg());
                    dataConnection = ComputerNode::connectToSocket(p);
                    if(dataConnection.id!=-1){
                        sendStatus(150);
                    }else{
                        sendStatus(500);
                    }
                } break;

                case RETRIVE:{
                    if (!isAuthorized){
                        sendStatus(404);
                        break;
                    }

                    sendStatus(250);

                    vector<char> raw = getFileContent(dataPath+input.getArg());
                    self.sendData(raw,dataConnection);
                } break;

                case LIST:{
                    if (!isAuthorized){
                        sendStatus(404);
                        break;
                    }

                    sendStatus(200);

                    string dataList = getAvailbleDataList();
                    vector<char> raw;
                    raw.resize(dataList.length());
                    memcpy(raw.data(),dataList.c_str(),dataList.length());
                    self.sendData(raw,clientControl);
                } break;

                case QUIT:{
                    sendStatus(221);
                    close(clientControl.id);
                    close(dataConnection.id);
                    exit(0);
                }

                default:{
                    sendStatus(401);
                }

            }
            



        }while(input.getCommand() != QUIT);



    }

};

int main(){
    FTPServer server(FTP_PORT);
    server.run();
}
