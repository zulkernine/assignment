#include<iostream>
#include<unordered_map>
#include <sstream>

#define FTP_PORT 8080
#define ARG_LENGTH 100

using namespace std;

enum FTPCommands{
    USER,
    PASSWORD,
    PORT,
    RETRIVE,
    QUIT,
    LIST,
    NoSuchCommand
};

const unordered_map<string, FTPCommands> StringToCommand = {
    { "USER", USER  },
    { "PASSWORD", PASSWORD  },
    { "PORT", PORT  },
    { "RETRIVE", RETRIVE  },
    { "QUIT", QUIT  },
    { "LIST", LIST  },
};

const std::unordered_map<int, string> FTPStatusCodeMessage = {
    {220, "Service ready."},
    {331, "Username Ok. Send password."},
    {230, "Login successfull, Kon'nichiwa 🎃🎃🎃"},
    {150, "Data connection opens shortly 🤝🤝🤝"},
    {200, "OK"},
    {250, "Request file action OK"},
    {226, "Closing Data connection"},
    {221, "Service closing. Goodbye senpai 👋👋👋"},
    {404, "Unauthorized access 😤😤😤"},
    {401, "Bad arguements recieved 🤢🤢🤢"},
    {500, "Internal server error, please try again 🥺🥺🥺"}
};

class UserInput{
    FTPCommands command;
    char args[ARG_LENGTH];
public:
    UserInput(){
        command = NoSuchCommand;
        args[0]='\0';
    }

    UserInput(string str){
        istringstream _stream(str);
        _stream>>args; // get command string
        
        auto _itr = StringToCommand.find(args);
        if(_itr != StringToCommand.end()){
            this->command = (_itr)->second;
        }
        else this->command = NoSuchCommand;
        
        _stream >> args;
    }

    FTPCommands getCommand(){ return command; }
    string getArg(){ return string(args); }
};

