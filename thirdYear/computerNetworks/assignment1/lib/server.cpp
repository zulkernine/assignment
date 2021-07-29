// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../header/errorDetection.hpp"
#include "../header/injecterror.hpp"

#define PORT 8080
using namespace std;

void server_task(int client, ifstream& input, ofstream& report);

int main(int argc, char const* argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    string hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        cerr << "socket failed";
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        cerr << "setsockopt";
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        cerr << "bind failed";
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0){
        cerr << "listen";
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
        cerr << "accept";
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, 1024);
    cout << buffer << "\n";

    ifstream input("random_binary_stings.txt", ios::in);
    ofstream output("detailed_report.txt", ios::out);
    int counter = 1;

    while (true){
        output << counter << "\n";
        server_task(new_socket, input, output);
        break;
    }
    input.close();
    output.close();

    return 0;
}

void server_task(int client, ifstream& input, ofstream& report){
    string binData; 
    input >> binData;   //Take binary data from text file
    report<<"DATA: "<<binData<<"\n";
    bool lrc,vrc,checksum,crc; //error detection status of each check from client

    //LRC or parity check
    string lrcEncoding = LRC::encodeData(binData);
    report<<"LRC:\t\t"<<lrcEncoding<<"\n";
    lrcEncoding = injectError(lrcEncoding);
    report<<"Erroneous LRC:\t\t"<<lrcEncoding<<"\n";
    send(client,lrcEncoding.c_str(),lrcEncoding.length(),0);
    read(client, (char*)&lrc, sizeof(lrc));
    cout << "Error Detected: \t\t" << (lrc ? "True":"False") << "\n";
}
