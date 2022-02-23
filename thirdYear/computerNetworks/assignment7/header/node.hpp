#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <sys/time.h>
#include <errno.h>

#define CHANNEL_PORT 8080
#define MAX_BUFFER_SIZE 16777216 // 16MB

using namespace std;

class ConnectionSocket{
public:
    int id; //descriptor
    struct sockaddr_in address;
    ConnectionSocket(){
        id = -1;
    }
};


long long int getCurrentTimestamp(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long int micros = tp.tv_sec * 1000000 + tp.tv_usec;
    return micros;
}

class ComputerNode{
    const int assignedPort;
    ConnectionSocket listenerSocket;

    static ConnectionSocket getConnecteionSocket(int port){
        ConnectionSocket sock;
        if ((sock.id = socket(AF_INET,SOCK_STREAM, 0)) < 0){
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
        if ((listenerSocket.id = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            cerr << "socket failed";
            exit(EXIT_FAILURE);
        }

        int opt = 1;
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

        listen(listenerSocket.id, incomingConnectionQueue);

        cout << "Started listening to port: " << port << "\n";
    }

    static ConnectionSocket acceptConnection(ConnectionSocket listenerSocket){
        int new_socket;
        ConnectionSocket sock;
        socklen_t addrlen = sizeof(sock.address);

        if ((new_socket = accept(listenerSocket.id, (struct sockaddr*)&(sock.address), (socklen_t*)&addrlen)) < 0){
            cerr << "can't accept";
            cout << "errno: " << errno << endl;
            throw string("Connection backlog queue is empty!\n");
        }
        sock.id = new_socket;

        return sock;
    }
    
    static ConnectionSocket connectToSocket(int port){
        ConnectionSocket destinaion;
        destinaion = getConnecteionSocket(port);

        int status = connect(destinaion.id, (const struct sockaddr*)&(destinaion.address),
            sizeof(destinaion.address));
        
        if(status != 0){
            cout << "Can't connect to dest port:" << port << "\nAborting :(\n\n";
            exit(1);
        }
        
        return destinaion;
    }

    ConnectionSocket getSelfListenerSocket(){ return listenerSocket; }

    bool sendData(vector<char> rawData, ConnectionSocket destination){
        int status = send(destination.id, rawData.data(), rawData.size() * sizeof(char),
            MSG_CONFIRM);
        
        if (status < 0){
            cout << "Filed to send packet, packet dropped\n";
        }

        return status >= 0;
    }

    int recieveData(vector<char>& rawData, ConnectionSocket source){
        try{
            rawData.resize(MAX_BUFFER_SIZE);

            int valread = recv(source.id, rawData.data(), rawData.size(), 0);
            if (valread > 0){
                rawData.resize(valread);
            }

            return valread;
        }
        catch (string s){
            cout << s;
        }
        return -1;
    }
};

