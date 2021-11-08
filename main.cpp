#include <iostream>
#include "string.h"
#include "unistd.h"
#include "vector"
#include "sys/wait.h"
#include "signal.h"
#include <fstream>
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
    // remove & from commands vector
    if(command.compare("&")!=0)
    commands.push_back(command);
     return commands;
 }
 void logger(int signal){
     ofstream fout;
     fout.open("log.txt",ios_base::app);
     // writing inside log.txt file
     fout<<"Child process was terminated"<<endl;
     fout.close();
 }
int main(){
        
    while(1){
         string userCommand="";
        // getline is a function that read a line from an input stream
        cout<<"Shell > ";
        getline(cin,userCommand);
        if(userCommand.compare("exit")==0){
            //    cout<<"exit"<<endl;
                _exit(1);
        }
        bool waitEnabled=true;
        if(userCommand[userCommand.size()-1]=='&'){
            waitEnabled=false;
        }
        /* once the child is terminated, the child sends a signal to the parent and executes the
        second parameter*/
        signal(SIGCHLD,logger);
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
            // cout<<"Child process"<<endl;
            if(execvp(args[0],args)<0){
                perror("Error in Execvp");
                _exit(1);
            }
        }
        else{
            if(waitEnabled){
                // cout<<"Wait enabled"<<endl;
                waitpid(pid,NULL,0);
            }
            // cout<<"Parent process"<<endl;
        }

    }
    return 0;
}