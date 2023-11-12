#ifndef AUDIO_LISTENER_HEADER
#define AUDIO_LISTENER_HEADER

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <lmcons.h>
#include <string>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>

void CALLBACK waveInCallback(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
int fillBuffer(WAVEFORMATEX &format, BYTE* bufferTabToWrite[], int bufferSize, int numSamples, bool &listenInProgress, int &buffersConsideredEmpty, int &buffersRecorded, bool &mustWriteBuffer);
int writeBuffersListOnWaveFile(WAVEFORMATEX &format, int &tailleTotale, int &buffersRecorded, BYTE* bufferTabToWrite[], int &numSamples, std::string nomFichier);
int listenOnce(std::string nomFichier);
std::string trouverNomFichier();
void constantListen();

#endif