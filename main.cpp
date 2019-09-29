#include <iostream>
#include <vector>
#include "unistd.h"
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <list>
#include <iterator>
#include <signal.h>

using namespace std;

int main(int argc, const char * argv[]) {
    string userData = "";
    
    vector<pid_t> ChildrenList;
    pid_t pid = 1;
    
    do{
        
        //If the user did not enter done, create another child program to create a new txt
        if(pid ==0){
            //Child Process
            
            ofstream ostr;
            pid_t currentPID = getpid();
            ostr.open("TextFileProcessNum" + to_string(currentPID)+".txt",ios::out|ios::app);
            
            ostr << userData << endl;
            ostr.close();
        }
        else if(pid > 0){
            //Parent Process
            cout<< "Please enter a string: ";
            cin>>userData;
            if(userData != "Done"){
                pid_t forkedPid = fork();
                //So in its current state, the below vector will exist in each thread but only be accurate in the parent thread, itll have 0s in the others.
                ChildrenList.push_back(forkedPid);
                pid = forkedPid;
            }
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    while(userData != "Done");
    
    
    //Kill all of the Children
    for(int i = 0; i<ChildrenList.size();i++){
        pid_t pidToKill = ChildrenList[i];
        kill(pidToKill, SIGTERM);
    }
    
    cout<<"Program ended."<<endl;
    
    return 0;
}
