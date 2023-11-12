#ifndef THREAD_FUNCTIONS_FOR_AUDIO_BUFFER_HANDLING
#define THREAD_FUNCTIONS_FOR_AUDIO_BUFFER_HANDLING

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <lmcons.h>
#include <string>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>

struct BufferAnalysStruct {
    int nSamples;
    int* buffersConsideredEmpty;
    int* buffersRecorded;
    BYTE* bufferTabForThread;
    bool* mustWriteBuffer;
};

DWORD WINAPI handleBufferAfterListen(LPVOID windowsPointerParams);
int startBufferAnalysisThread(int nSamples, int* buffersConsideredEmpty, int* buffersRecorded, BYTE* bufferTabForThread, bool *mustWriteBuffer);

#endif