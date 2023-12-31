#include "../headers/headers.hpp"

using namespace std;

int convertFromBytesToInteger(BYTE byte1, BYTE byte2, BYTE byte3, BYTE byte4){
    int result = 0;

    result |= static_cast<int>(byte4) << 24;
    result |= static_cast<int>(byte3) << 16;
    result |= static_cast<int>(byte2) << 8;
    result |= static_cast<int>(byte1);

    return result;
}

void convertFromBufferToIntegerTab(BYTE* buffer, int bufferSize, int* conversionTab){
    for (int i = 0; i<bufferSize; i = i + 3) {
        *(conversionTab+(int)(i/3)) = convertFromBytesToInteger(buffer[i],buffer[i+1], buffer[i+2], 0x00);
    }
}

unsigned int getAverageFromTab(unsigned int* bufferTab, int bufferSize){
    if (bufferSize <= 0) {
        // Gestion du cas où le tableau est vide pour éviter une division par zéro.
        std::cerr << "Erreur: Buffer vide" << std::endl;
        return 0;
    }
    unsigned long long sum = 0;
    for (int i = 0; i<bufferSize; i++){
        sum += bufferTab[i];
    }
    return (unsigned int)(sum/bufferSize);
}