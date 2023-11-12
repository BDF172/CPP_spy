#include "../headers/headers.hpp"

using namespace std;

int convertFromBytesToInteger(BYTE byte1, BYTE byte2, BYTE byte3, BYTE byte4){
    unsigned char result[4] = {byte1, byte2, byte3, byte4};

    int intValue = 0;
    for (int i = 3; i >= 0; i--) {
        intValue = (intValue << 8) | result[i];
    }

    return intValue;
}

void convertFromBufferToIntegerTab(BYTE* buffer, int bufferSize, int* conversionTab){
    for (int i = 0; i<bufferSize; i = i + 3) {
        int test = convertFromBytesToInteger(buffer[i],buffer[i+1], buffer[i+2], 0x00);
        *(conversionTab+(int)(i/3)) = test;
    }
}

unsigned int getAverageFromTab(unsigned int* bufferTab, int bufferSize){
    unsigned long long sum = 0;
    for (int i = 0; i<bufferSize; i++){
        sum += bufferTab[i];
    }
    return static_cast<unsigned int>(sum/bufferSize);
}