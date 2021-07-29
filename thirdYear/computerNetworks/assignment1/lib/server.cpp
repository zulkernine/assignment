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

    ifstream input("random_binary_stings.txt", ios::in);
    ofstream output("detailed_report.txt", ios::out);
    int counter = 1;

    while (!input.eof()){
        output << counter << "\n";
        server_task(new_socket, input, output);
        cout<<(counter++)<<"\n";
    }
    send(new_socket, "\0", 1, 0);

    input.close();
    output.close();

    return 0;
}

void server_task(int client, ifstream& input, ofstream& report){
    string binData;int bitFlips;
    input >> binData;   //Take binary data from text file
    report << "DATA:\t\t\t\t\t" << binData << "\n";
    bool lrc, vrc, checksum, crc; //error detection status of each check from client

    //LRC or parity check
    string lrcEncoding = LRC::encodeData(binData);
    report << "LRC:\t\t\t\t\t" << lrcEncoding << "\n";
    lrcEncoding = injectError(lrcEncoding, bitFlips);
    report << "Erroneous LRC:\t\t\t" << lrcEncoding << "\tBit Flips: " << bitFlips << "\n";
    send(client, lrcEncoding.c_str(), lrcEncoding.length(), 0);
    read(client, (char*)&lrc, sizeof(lrc));
    report << "Error Detected: \t\t" << (lrc ? "True" : "False") << "\n";

    //VRC or 2d check
    string vrcEncoding = VRC::encodeData(binData);
    report << "VRC:\t\t\t\t\t" << vrcEncoding << "\n";
    vrcEncoding = injectError(vrcEncoding, bitFlips);
    report << "Erroneous VRC:\t\t\t" << vrcEncoding << "\tBit Flips: " << bitFlips << "\n";
    send(client, vrcEncoding.c_str(), vrcEncoding.length(), 0);
    read(client, (char*)&vrc, sizeof(vrc));
    report << "Error Detected: \t\t" << (vrc ? "True" : "False") << "\n";

    //Checksum
    string checksumEncoding = CheckSum::encodeData(binData);
    report << "Checksum:\t\t\t\t" << checksumEncoding << "\n";
    checksumEncoding = injectError(checksumEncoding, bitFlips);
    report << "Erroneous Checksum:\t\t" << checksumEncoding << "\tBit Flips: " << bitFlips << "\n";
    send(client, checksumEncoding.c_str(), checksumEncoding.length(), 0);
    read(client, (char*)&checksum, sizeof(checksum));
    report << "Error Detected: \t\t" << (checksum ? "True" : "False") << "\n";

    //CRC
    string crcEncoding = CRC::encodeData(binData);
    report << "CRC:\t\t\t\t\t" << crcEncoding << "\n";
    crcEncoding = injectError(crcEncoding, bitFlips);
    report << "Erroneous CRC:\t\t\t" << crcEncoding << "\tBit Flips: " << bitFlips << "\n";
    send(client, crcEncoding.c_str(), crcEncoding.length(), 0);
    read(client, (char*)&crc, sizeof(crc));
    report << "Error Detected: \t\t" << (crc ? "True" : "False") << "\n";
    report<<"Final Status: "<<lrc<<vrc<<checksum<<crc<<"\n\n\n";
}
