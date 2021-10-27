#include <iostream>
#include "string.h"
#include "unistd.h"
#include "vector"
#include "sys/wait.h"
using namespace std;

/**
 * function that splits the string command into vector of strings.
 *
 * @param values userCommand that the user entered
 * @return vector of strings
 */ 
 vector<string> splitCommands(string userCommand){
    string command="";
    vector<string>commands;
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
     return commands;
 }
int main(){
        
    while(1){
         string userCommand="";
        // getline is a function that read a line from an input stream
        getline(cin,userCommand);
        pid_t pid=fork();
        if(pid<0){
            perror("Fork Failed");
            _exit(1);
        }
        vector<string>commands=splitCommands(userCommand);
        int numOfCommands=commands.size();
        char * args[numOfCommands+1];

        // set last pointer to NULL
        args[numOfCommands]=NULL;
        int index=0;
        for(int i=0;i<commands.size();i++){
            args[index]=(char *)commands[i].c_str();
            index++;
        }
        // child process
        if(pid==0){
            if(commands[0].compare("exit")==0){
                cout<<"exit"<<endl;
                _exit(1);
            }
            if(execvp(args[0],args)<0){
                perror("Error in Execvp");
                _exit(1);
            }
        }
        else{
            if(commands[0].compare("exit")==0){
                cout<<"exit"<<endl;
                _exit(1);
            }
        }

    }
    return 0;
}