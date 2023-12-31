#ifndef AUDIO_LISTENER_HEADER
#define AUDIO_LISTENER_HEADER

void CALLBACK waveInCallback(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
int fillBuffer(WAVEFORMATEX &format, BYTE* bufferTabToWrite[], int bufferSize, int numSamples, bool &listenInProgress, int &buffersConsideredEmpty, int &buffersRecorded, bool &mustWriteBuffer);
int writeBuffersListOnWaveFile(WAVEFORMATEX &format, int &tailleTotale, int &buffersRecorded, BYTE* bufferTabToWrite[], int &numSamples, std::string nomFichier);
int listenOnce(std::string nomFichier);
std::string trouverNomFichierWave();
void constantListen();

#endif