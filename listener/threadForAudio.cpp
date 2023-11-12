#include "../headers/headers.hpp"

using namespace std;

DWORD WINAPI handleBufferAfterListen(LPVOID windowsPointerParams) {
    BufferAnalysStruct* structureThread = (BufferAnalysStruct*)(windowsPointerParams);

    BYTE* bufferTabForThread = (BYTE*)(structureThread->bufferTabForThread);
    int* buffersRecorded = (structureThread->buffersRecorded);
    int* buffersConsideredEmpty = structureThread->buffersConsideredEmpty;
    int nSamples = structureThread->nSamples;

    int* bufferIntegersTab = (int*)malloc(sizeof(int) * nSamples);
    long long int sum = 0;
    int nombreAdditionnes = 0;
    int tamponPourTableauInt;

    for (int i = 0; i < nSamples; i++) {
        int bufferState = 3 * i;
        tamponPourTableauInt = convertFromBytesToInteger(bufferTabForThread[bufferState],                  
                                                         bufferTabForThread[bufferState + 1],              
                                                         bufferTabForThread[bufferState + 2],              
                                                         0x00);                                                             
        if (tamponPourTableauInt < 10000000 && tamponPourTableauInt > 0) {
            *(bufferIntegersTab+i) = tamponPourTableauInt;
            sum += *(bufferIntegersTab+i);
            nombreAdditionnes++;
        }
    }
    sum /= nombreAdditionnes;
    if (sum > 7000) {
        if (++(*buffersRecorded) == 1024) {
            free(bufferIntegersTab);  // Libérer la mémoire avant de quitter la fonction
            *(structureThread->mustWriteBuffer) = true;
        }
    } else if (*buffersRecorded > 0) {
        (*buffersConsideredEmpty)++;
        (*buffersRecorded)++;
        if (*buffersConsideredEmpty == 1) {
            free(bufferIntegersTab);  // Libérer la mémoire avant de quitter la fonction
            *(structureThread->mustWriteBuffer) = true;
        }
    }
    else {
        free(bufferIntegersTab);
    }
}

int startBufferAnalysisThread(int nSamples, int* buffersConsideredEmpty, int* buffersRecorded, BYTE* bufferTabForThread, bool *mustWriteBuffer) {
    BufferAnalysStruct maStruct;
    maStruct.nSamples = nSamples; maStruct.buffersConsideredEmpty = buffersConsideredEmpty; maStruct.buffersRecorded = buffersRecorded;
    maStruct.bufferTabForThread = bufferTabForThread; maStruct.mustWriteBuffer = mustWriteBuffer; LPVOID windowsPointerParams = &maStruct;
    if(CreateThread(NULL, 0, &handleBufferAfterListen, windowsPointerParams, 0, 0)==NULL){
        cerr << "Erreur lors de la création du thread : " << GetLastError() << endl;
        return -1;  // Ou tout autre code d'erreur approprié
    }
    Sleep(1);

    return 0;
}