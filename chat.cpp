/*******************************************
* Group Name  : XXXXXX

* Member1 Name: XXXXXX
* Member1 SIS ID: XXXXXX
* Member1 Login ID: XXXXXX

* Member2 Name: XXXXXX
* Member2 SIS ID: XXXXXX
* Member2 Login ID: XXXXXX
********************************************/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

void helpMessage(){
    printf("\nMake sure to run the client side this way:\n");
    printf("./chat -p [PORT NUMBER] -s [IP ADDRESS]\n\n");
    printf("Make sure to run the server side this way:\n");
    printf("./chat\n\n");
}

bool validPortNumber(char *port){
    size_t len = strlen(port);
    for(size_t i = 0; i<len; i++){
        char c = port[i];
        if(!isdigit(c)){
            return false;
        }
        // printf("%c ",c);
    }
    // printf(port);
    // printf("\n%lu\n", len);
    return true;
}

bool validIpAddress(char* ip){
    size_t len = strlen(ip);
    for(size_t i =0; i<len; i++){
        char c = ip[i];
        
    }
}

int main(int argc, char* argv[]){
    // printf("Hello, World\n");
    // for(int i = 0; i<argc; i++){
    //     printf(argv[i]);
    //     printf("\n");
    // }
    int portNumber = 0;
    char* ipAddress = "";

    //Port then ip
    if(!strcmp(argv[1],"-p") && !strcmp(argv[3],"-s")){
        // printf("port is %s\n", argv[2]);
        // printf("IP is %s\n", argv[4]);
        if(validPortNumber(argv[2])){
            printf("VALID PORT NUMBER");
        } else{
            printf("\nINVALID PORT NUMBER\n");
            helpMessage();
            return 1;
        }
        
    }

    //ip then port


    //Print Help message
    if(!strcmp(argv[1],"-h")){
        helpMessage();
    }
    return 0;
}
