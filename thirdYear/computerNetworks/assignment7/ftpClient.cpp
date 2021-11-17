#include "./header/node.hpp"
#include "./header/ftpProtocolConstant.hpp"
#include<fstream>
#include<thread>

class FTPClient{
    ComputerNode self;
    ConnectionSocket clientControl; // for control connection
    ConnectionSocket dataConnection; // for data connection
    string fileName;

    void saveData(vector<char>& data){
        ofstream output(fileName, ios::out | ios::binary);
        output.write(data.data(),data.size());
        output.close();
        cout << "\tDATA_Connection> File saved to "<<fileName<<"\n";
    }

    vector<char> makeRawData(UserInput ui){
        vector<char> raw;
        raw.resize(sizeof(ui));
        memcpy(raw.data(),(char*)&ui,sizeof(ui));
        return raw;
    }

    string getStatus(vector<char>& response){
        int status;
        memcpy((char*)&status,response.data(),sizeof(status));
        return FTPStatusCodeMessage.at(status);
    }
    void startDataConnectionThread(){
        // spawn data recieving socket
        thread datahandling(&FTPClient::handleDataConnection, this);
        datahandling.detach();
    }
    string getMessage(vector<char>& response){
        return string(response.begin(),response.end());
    }
public:
    FTPClient(int port):self(port){
        cout<<"FTP client initiated\n\n";
    }

    void handleDataConnection(){
        while(true){
            dataConnection =  ComputerNode::acceptConnection(self.getSelfListenerSocket());
            vector<char> data;
            self.recieveData(data,dataConnection);
            saveData(data);
            break;
        }
    }



    void run(){
        clientControl =  ComputerNode::connectToSocket(FTP_PORT);
        vector<char> raw;
        self.recieveData(raw, clientControl);
        cout << getStatus(raw) << "\n\n";

        while(true){
            cout<<"ftp> ";
            string inputString;
            getline(cin,inputString);
            UserInput ui(inputString);

            if (ui.getCommand() == RETRIVE) fileName = "recieved_" + ui.getArg();

            raw = makeRawData(ui);
            self.sendData(raw,clientControl);
            self.recieveData(raw,clientControl);
            cout<<getStatus(raw)<<"\n\n";

            switch(ui.getCommand()){
                case LIST:{
                    self.recieveData(raw, clientControl);
                    cout << "Server files:\n";
                    cout << getMessage(raw) << "\n\n";
                } break;

                case QUIT:{
                    cout << "Shutting down client 😁\n";
                    exit(0);
                } break;

                case RETRIVE:{
                    startDataConnectionThread();
                }

            }
        }
    }

};

int main(){
    // cout<<"FTP client port: ";
    // int port;
    // cin>>port;
    FTPClient client(8000);
    cout<<"Please use this same port number with PORT command :)\n\n";
    client.run();
}
