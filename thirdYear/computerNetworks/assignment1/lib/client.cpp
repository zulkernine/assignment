// Client side C/C++ program to demonstrate Socket programming
#include<iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../header/errorDetection.hpp"
#include "../header/injecterror.hpp"

#define PORT 8080
using namespace std;


void client_task(int server){
    char buffer[128] = { 0 };
    bool status;

    //LRC
    read(server, buffer, 128);
    if(buffer[0] == '\0') exit(0);//server has terminated

    string data(buffer);
    status = LRC::hasError(data);
    send(server, (char*)&status, sizeof(status), 0);

    //VRC
    for(int i=0;i<128;i++) buffer[i] = 0;
    read(server, buffer, 128);
    data = string(buffer);
    status = VRC::hasError(data);
    send(server, (char*)&status, sizeof(status), 0);

    //Checksum
    for (int i = 0;i < 128;i++) buffer[i] = 0;
    read(server, buffer, 128);
    data = string(buffer);
    status = CheckSum::hasError(data);
    send(server, (char*)&status, sizeof(status), 0);

    //CRC
    for (int i = 0;i < 128;i++) buffer[i] = 0;
    read(server, buffer, 128);
    data = string(buffer);
    status = CRC::hasError(data);
    send(server, (char*)&status, sizeof(status), 0);
}


int main(int argc, char const* argv[]){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "\nConnection Failed \n";
        return -1;
    }
    
    while (true){
        try{
            client_task(sock);
        }catch(string e){
            cout<<e<<"\n";
        }
    }
    return 0;
}
