#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <cstring>
#define CHANNEL_PORT 8080

using namespace std;

class ComputerNode{
    const int assignedPort;
    ConnectionSocket listenerSocket;
    char buffer[1024] = { 0 };

    ConnectionSocket getConnecteionSocket(int port){
        ConnectionSocket sock;
        if ((sock.id = socket(AF_INET, SOCK_STREAM, 0)) == 0){
            cerr << "socket failed";
            exit(EXIT_FAILURE);
        }

        sock.address.sin_family = AF_INET;
        sock.address.sin_port = htons(port);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, "127.0.0.1", &sock.address.sin_addr) <= 0){
            cout << "\nInvalid address/ Address not supported \n";
            // return 0;
            exit(1);
        }

        return sock;
    }

public:
    ComputerNode(int port, int incomingConnectionQueue = 3) :assignedPort(port){
        // Creating socket file descriptor
        if ((listenerSocket.id = socket(AF_INET, SOCK_STREAM, 0)) == 0){
            cerr << "socket failed";
            exit(EXIT_FAILURE);
        }

        int opt = 1;
        // Forcefully attaching socket to the port 8080
        if (setsockopt(listenerSocket.id, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
            cerr << "setsockopt";
            exit(EXIT_FAILURE);
        }
        listenerSocket.address.sin_family = AF_INET;
        listenerSocket.address.sin_addr.s_addr = INADDR_ANY;
        listenerSocket.address.sin_port = htons(port);

        // Forcefully attaching socket to the port 8080
        if (bind(listenerSocket.id, (struct sockaddr*)&(listenerSocket.address), sizeof(listenerSocket.address)) < 0){
            cerr << "bind failed";
            exit(EXIT_FAILURE);
        }
        if (listen(listenerSocket.id, incomingConnectionQueue) < 0){
            cerr << "listen";
            exit(EXIT_FAILURE);
        }
    }

    ConnectionSocket acceptConnection()throw (string){
        //Set socket in non-blocking mode
        int flags = fcntl(listenerSocket.id, F_GETFL, 0);
        if (fcntl(listenerSocket.id, F_SETFL, flags | O_NONBLOCK) < 0){
            cerr << ("fcntl(F_SETFL) can't set socket to non_block mode");
            exit(EXIT_FAILURE);
        }

        int new_socket;
        ConnectionSocket sock;
        socklen_t addrlen = sizeof(sock.address);
        if ((new_socket = accept(listenerSocket.id, (struct sockaddr*)&(sock.address), (socklen_t*)&addrlen)) < 0){
            cerr << "accept";
            throw string("Connection backlog queue is empty!");
        }
        sock.id = new_socket;

        //Set socket back to blocking mode
        flags = fcntl(listenerSocket.id, F_GETFL, 0);
        if (fcntl(listenerSocket.id, F_SETFL, flags ^ O_NONBLOCK) < 0){
            cerr << ("fcntl(F_SETFL) can't set socket back to blocking mode");
            exit(EXIT_FAILURE);
        }

        return sock;
    }

    void sendData(vector<char> rawData, bool sendToChannel = true){
        ConnectionSocket destinaion;
        if (sendToChannel){
            destinaion = getConnecteionSocket(CHANNEL_PORT);
        }
        else{
            DataHeader h;
            memcpy(&h, rawData.data(), sizeof(DataHeader));
            destinaion = getConnecteionSocket(h.destPort);
        }

        if (connect(destinaion.id, (struct sockaddr*)&(destinaion.address), sizeof(destinaion.address)) < 0){
            cout << "\nConnection Failed \n";
            exit(1);
        }

        int status = send(destinaion.id, rawData.data(), rawData.size() * sizeof(char), 0);
        if (status == -1){
            cout << "Filed to send\n";
            exit(1);
        }
    }

    int recieveData(vector<char>& rawData){
        try{
            rawData.resize(1024);
            ConnectionSocket source = acceptConnection();
            int valread = read(source.id, rawData.data(), 1024);

            if (valread > 0){
                DataHeader h;
                memcpy(&h, rawData.data(), sizeof(DataHeader));
                rawData.resize(sizeof(DataHeader) + h.length * sizeof(char));
            }
            return valread;

        }
        catch (string e){
            cerr << e;
            return -1;
        }
    }
};

class ConnectionSocket{
public:
    int id; //descriptor
    struct sockaddr_in address;
    ConnectionSocket(){
        id = -1;
    }
};

struct DataHeader{
    char startByte;
    int sourcePort;
    int destPort;
    NetworkDataType type;
    int length; // Length of actual data + 16 bit crc flag
};


enum NetworkDataType{ RAW_DATA, ACK, NCK, COMPLETION_ACK };
/*
 * COMPLETION_ACK: file is completely transmitted
 * RAW_DATA : binary data
*/
