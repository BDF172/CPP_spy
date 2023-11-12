// #include "../headers/headers.hpp"
#include <iostream>
#include <WinSock2.h>
#include <windows.h>

using namespace std;

int test(void){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        cerr << "WSAStartup failed" << endl;
        return 1;
    }
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname("127.0.0.1");
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(4444);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long *)host->h_addr);
    cout << "Connecting..." << endl;
    if(connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
        cerr << "Could not connect" << endl;
        return 1;
    }
    cout << "Connected" << endl;
    
    return 0;
}

int main(){
    return test();
}