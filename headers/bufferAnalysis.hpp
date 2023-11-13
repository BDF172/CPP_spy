#ifndef BUFFER_ANALYSIS_FUNCTIONS
#define BUFFER_ANALYSIS_FUNCTIONS

int convertFromBytesToInteger(BYTE byte1, BYTE byte2, BYTE byte3, BYTE byte4);
void convertFromBufferToIntegerTab(BYTE* buffer, int bufferSize, int* conversionTab);
unsigned int getAverageFromTab(unsigned int* bufferTab, int bufferSize);

#endif