#ifndef SERVER_COMMUNICATIONS_HEADER
#define SERVER_COMMUNICATIONS_HEADER

int sendFile(std::string fileName);
std::string getFileNameFromString(std::string &fileNames);
void continuousFileSend(void);


#endif