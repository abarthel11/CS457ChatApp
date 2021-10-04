/*******************************************
* Group Name  : Multipoint

* Member1 Name: Austin Barthel
* Member1 SIS ID: 833200684
* Member1 Login ID: abarth11

* Member2 Name: XXXXXX
* Member2 SIS ID: XXXXXX
* Member2 Login ID: XXXXXX
********************************************/

/*   
    VALID
    ./chat -p 3360 -s 192.82.47.232
    ./chat -h
    ./chat -s 192.82.47.232 -p 3360
    INVALID
    ./chat -p 3360a -s 192.82.47.232
    ./chat -p 3360 -s 192.82.47a.232
    ./chat -p 3360a -s 192.82.47a.232
    ./chat -l
    ./chat -s 192.82.47.232a -p 3360
    ./chat -s 192.82.47.232 -p 3360a
    ./chat -s 192.82.47.232a -p 3360a
    
*/


#include <iostream>
#include <string>
#include <regex>
using namespace std;

//DO ACTUAL ASSIGNMENT STUFF
void serverStart(){
    cout << "Waiting for connection to client...\n";
    while(true){
    }
}

void clientStart(string ipAddress,string portNum){
    cout << "Connecting to server...\n";
    cout << "Listening on PORT " << portNum << "\n";
    while(true){
    }
}

//VALIDATION SECTION
void helpMessage(bool invalidInput=false){
    if(invalidInput){
        cout << "\nINVALID INPUT\n";
    }
    cout << "\nMake sure to run the client side this way:\n";
    cout << "./chat -p [PORT NUMBER] -s [IP ADDRESS]\n\n";
    cout << "Or this way:\n";
    cout << "./chat -s [IP ADDRESS] -p [PORT NUMBER]\n\n";
    cout << "Make sure to run the server side this way:\n";
    cout << "./chat\n\n";
}

void invalidMessage(bool portInvalid, bool ipInvalid){
    string portMessage = "\nInvalid Port Number. Must only be digits.\n";
    string ipMessage = "\nInvalid IP Address. Must be in IPv4 syntax. (X.X.X.X)\n";
    if(portInvalid && ipInvalid){ //both invalid
        cout << portMessage;
        cout << ipMessage;
        helpMessage(true);
    } else if(portInvalid && !ipInvalid){ //only port invalid
        cout << portMessage;
        helpMessage(true);
    } else if(!portInvalid && ipInvalid){ //only ip invalid
        cout << ipMessage;
        helpMessage(true);
    }
}

// ^[0-9]*$
bool validPortNum(string portNum){
    if(!regex_match(portNum,regex("(\\+|-)?[[:digit:]]+"))){
        // cout << "test";
        return false;
    }
    return true;
}

// ^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$
bool validIpAddress(string ipAddress){
    if(!regex_match(ipAddress,regex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$"))){
        return false;
    }
    return true;
}

bool validValues(string portNum, string ipAddress, bool &portInvalid,bool &ipInvalid){
    if(!validIpAddress(ipAddress)){
        ipInvalid = true;
    }
    if(!validPortNum(portNum)){
        portInvalid = true;
    }
    if(portInvalid || ipInvalid){
        return false;
    }
    return true;
}

int main(int argc, char* argv[]){
    string portNum;
    string ipAddress;
    bool portInvalid=false;
    bool ipInvalid = false;

    if(argc == 5){ //client 
        string flag1 = argv[1];
        string followFlag1 = argv[2];
        string flag2 = argv[3];
        string followFlag2 = argv[4];
        if(flag1=="-p" && flag2 == "-s"){
            // cout <<"port then ip\n";
            portNum = followFlag1;
            ipAddress = followFlag2;
            if(!validValues(portNum,ipAddress,portInvalid,ipInvalid)){
                // cout << "invalid chech\n";
                // cout << portInvalid << ipInvalid << "\n";
                invalidMessage(portInvalid,ipInvalid);
                return -1;
            } else{
                clientStart(ipAddress,portNum);
            }
        } else if(flag1=="-s" && flag2=="-p"){
            portNum = followFlag2;
            ipAddress = followFlag1;
            if(!validValues(portNum,ipAddress,portInvalid,ipInvalid)){
                // cout << "invalid chech\n";
                // cout << portInvalid << ipInvalid << "\n";
                invalidMessage(portInvalid,ipInvalid);
                return -1;
            } else{
                clientStart(ipAddress,portNum);
            }
            
        } else {
            helpMessage(true);
            return -1;
        }

    } else if(argc == 2){ //print help message
        string flag = argv[1];
        if(flag == "-h"){
            helpMessage();
            return 0;
        }else{
        helpMessage(true);
        return -1;
        }
    } else if(argc ==1){ //server
        serverStart();
    }
    return 0;
}