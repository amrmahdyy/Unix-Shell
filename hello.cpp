#include <iostream>
#include "string.h"
#include "unistd.h"
#include "vector"
#include "sys/wait.h"
using namespace std;
int main(){
    string userCommand="";
    // getline is a function that read a line from an input stream
    getline(cin,userCommand);
    vector<string>commands;
    string command="";
    for(int i=0;i<userCommand.size();i++){
        if(userCommand[i]==' '){
            // store the command in commands vector
            commands.push_back(command);
            // set command to empty
            command="";
        }
        else command+=userCommand[i];
    }
    commands.push_back(command);
    int numOfCommands=commands.size();
    char * args[numOfCommands+1];
    // set last pointer to NULL
    args[numOfCommands]=NULL;
    int index=0;
    for(int i=0;i<commands.size();i++){
        args[index]=(char *)commands[i].c_str();
        index++;
    }
    if(execvp(args[0],args)==-1){
        "Error in execvp";
    }
    return 0;
}