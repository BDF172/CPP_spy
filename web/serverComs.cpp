#include "../headers/headers.hpp"

using namespace std;

int getFileContent(string fileName, string &fileContent){
    ifstream file(fileName.c_str(), ios::binary);
    if (!file.is_open()){
        cout << fileName;
        cerr << "Impossible d'ouvrir le fichier" << endl;
        return 1;
    }

    ostringstream content;
    content << file.rdbuf();
    file.close();
    fileContent = content.str();
    return 0;
}

int sendFile(string fileName){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        cerr << "WSAStartup failed" << endl;
        return 1;
    }
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname("127.0.0.1");
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(80);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long *)host->h_addr);
    cout << "Connecting..." << endl;
    if(connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
        cerr << "Could not connect" << endl;
        return 1;
    }
    cout << "Connected" << endl;
    vector<string> header;
    vector<string> content;
    string fileContent;
    getFileContent(fileName, fileContent);

    content.push_back("--my_boundary\r\n");
    content.push_back("Content-Disposition: form-data; name=\"archiveWWW\"; filename=\"" + fileName + "\"\r\n");
    content.push_back("Content-Type: audio/wav\r\n\r\n");
    content.push_back(fileContent);
    content.push_back("\r\n--my_boundary--\r\n");

    int contentSizeToSend;

    for (string i : content){
        contentSizeToSend += i.size();
    }

    header.push_back("POST /webApp/upload.inc.php HTTP/1.1\r\n");
    header.push_back("Host: 127.0.0.1\r\n");
    header.push_back("Content-Type: multipart/form-data; boundary=my_boundary\r\n");
    header.push_back((string)"Content-Length: " + to_string(contentSizeToSend) + "\r\n");
    header.push_back("Connection: close\r\n\r\n");

    for(string line : header){
        send(Socket, line.c_str(), line.size(), 0);
    }

    for(string line : content){
        send(Socket, line.c_str(), line.size(), 0);
        Sleep(10);
    }

    system(("del " + fileName).c_str());

    return 0;
}

string getFileNameFromString(string &fileNames){
    string toReturn = fileNames.substr(0, fileNames.find_first_of('\n'));
    fileNames = fileNames.find_first_of('\n') == fileNames.size() - 1
    ?  ""
    :  fileNames.substr(fileNames.find_first_of('\n') + 1, fileNames.size());
    return toReturn;
}

void continuousFileSend(){
    Sleep(1000);
    string fileNames = *(filesToPostSend.load());
    if(fileNames.size() != 0) {
        string fileNameToSend = getFileNameFromString(fileNames);
        *(filesToPostSend.load()) = fileNames;
        sendFile(fileNameToSend);
    }
}