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

    Message too long:
    With arguments, the program acts as a client connects to a waiting server using the information provided. With one argument, the program prints.

    Ok message:
    With arguments, the program acts as a client connects to a waiting server using the information provided. With one argument, the program.
*/


#include <iostream>
#include <string>
#include <regex>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;

#define BACKLOG 10
#define PORTNUM "3790"


string getHostIP() {
	char name[32];
	gethostname(name, sizeof name);
	struct in_addr **addr_list = (struct in_addr **)gethostbyname(name)->h_addr_list;
	return inet_ntoa(*addr_list[0]);
}

void testaddrinfor(string address, string portnum)
{
    struct addrinfo hints, *res;
    const char *c_address = address.c_str();
    const char *c_portnum = portnum.c_str();
    char ipstr[INET6_ADDRSTRLEN];
    int sock_fd;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *p;
    getaddrinfo(c_address, c_portnum, &hints, &res) ;
    
    for(p = res ; p!=NULL; p= p->ai_next){
        sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        void *addr;
        addr = &(ipv4->sin_addr);
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);

        // cout << "yeheyh--->"<<ipstr << "\n";
        if(sock_fd == -1)
            continue;
        if(connect(sock_fd, p->ai_addr, p->ai_addrlen) != -1){
            // cout<<"SUCSESSSS";
            break;
        }
    }
    if(p == NULL){
        cout<< stderr << "couldnot connect \n";
    }
    cout << "Connecting to server...\n";
    // cout << "Listening on PORT " << portnum << "\n";
    cout << "Connected to a friend! You send first.\n";
    
    while (true)
    {
        char message[100];
        char buffer[1024] = {0};
        cout << "You: ";
        scanf("%s", message);
        send(sock_fd, message, strlen(message), 0);
        read(sock_fd, buffer, 1024);
        cout << "Friend: "<<buffer << "\n";

    }

}
//DO ACTUAL ASSIGNMENT STUFF
void serverStart(){

    string host_addr = getHostIP();	
    cout << "Welcome to Chat!\n";
    cout << "Waiting for a connection on " << host_addr << " port " << PORTNUM<<"\n";
    struct sockaddr_storage their_addr;
    socklen_t addr_size ;
    struct addrinfo hints, *res;
    int sock_fd; 
    bool runChat=true;
    //IPv4 of ferrari machine: 129.82.44.57

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORTNUM, &hints, &res);
    sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int bindVal = bind(sock_fd, res->ai_addr, res->ai_addrlen);

    if(bindVal == -1){
        cerr << "Failed to bind\n";
        runChat = false;
    }
    else{
        listen(sock_fd, BACKLOG);

    }

    addr_size = sizeof their_addr;
    int client_fd =accept(sock_fd, (struct sockaddr *)&their_addr, &addr_size);

    if(runChat)
        cout << "Found a friend! You receive first.\n";
    
    while (runChat)
    {
        char buffer[1024] = {0};
        char message[100];
        read(client_fd, buffer, 1024);
        cout << "Friend: "<<buffer << "\n";
        cout << "You: ";
        scanf("%s", message);
        send(client_fd, message, strlen(message), 0);

    }
    close(client_fd);
    

}

void clientStart(string ipAddress,string portNum){
    testaddrinfor(ipAddress, portNum);
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
