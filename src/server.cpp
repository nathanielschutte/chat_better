#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 2) {
        cerr << "Usage: port" << endl;
        exit(0);
    }

    int port = atoi(argv[1]);
    char msg[1000];

    // sockaddr_in is a c struct containing an internet address
    // contains:
    // short sin_family; AF_NET for internet space (AF_UNIX for local unix space)
    // u_short sin_port; contains port number (16 bit)
    // struct in_addr sin_addr; contains IP address of host
    // char sin_zero[8]; must be zero, unused
    sockaddr_in servAddr;
    bzero((char*) &servAddr, sizeof(servAddr));
    
    // address type is internet
    servAddr.sin_family = AF_INET;

    // set address to IP address of this host.  htonl set address byte order to internet byte order
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // set port to given port numbre
    servAddr.sin_port = htons(port);

    // open stream oriented socket (TCP) using SOCK_STREAM (datagram socket would be SOCK_DGRAM, with UDP)
    // TCP and UDP are appropriately chosen by setting third arg to 0 (based on second arg)
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0) {
        cerr << "Error establishing server socket" << endl;
    }
    
    // bind socket to local address specified by servAddr
    int bindSt = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindSt < 0) {
        cerr << "Error binding socket to local address" << endl;
    }

    cout << "Waiting for a client to connect..." << endl;
    
    // listen for up to 5 requests at a time, common maximum for most hardware
    listen(serverSd, 5);
   
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // accept new connection from client, blocks until that happens.
    int newSd = accept(serverSd, (struct sockaddr*) &newSockAddr, &newSockAddrSize);
    if(newSd < 0) {
        cerr << "Error accepting request from client" << endl;
        exit(1);
    }
    
    cout << "Connected with client" << endl;
    
    // track time and data
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;
    while(1) {
        cout << "..." << endl;
        memset(&msg, 0, sizeof(msg));
        bytesRead += recv(newSd, (char*) &msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit")) {
            cout << "Client has quit the session" << endl;
            break;
        }

        cout << "Client: " << msg << endl;
        cout << ">";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        if(data == "exit") {
            send(newSd, (char *) &msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(newSd, (char *) &msg, strlen(msg), 0);
    }

    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "*****Session*****" << endl;
    cout << "Bytes written: " << bytesWritten << "Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;


}
