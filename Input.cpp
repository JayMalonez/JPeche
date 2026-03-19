#include "Input.h"
#include  "Lib/json.hpp"

COM_Serial::COM_Serial(string port, DWORD baudRate) {
    connected = false;
    portName = "\\\\.\\" + port;

    // Initializing an object of wstring
    wstring temp = wstring(portName.begin(), portName.end());

    // Applying c_str() method on temp
    LPCWSTR wideString = temp.c_str();

    hSerial = CreateFile(wideString, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erreur : Impossible d'ouvrir le port " << port << endl;
        return;
    }

    // Configuration du port
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Erreur : Impossible d'obtenir l'etat du port." << endl;
        return;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Erreur : Impossible de configurer les parametres serie." << endl;
        return;
    }

    // Configuration des timeouts
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    connected = true;
}

COM_Serial::~COM_Serial(){
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
 }
}

int COM_Serial::joystickPotX() {

    json messages;
    
    readMSG();

    return 0;
 }

int COM_Serial::joystickPotY(){ return 0; }
//bouton
bool COM_Serial::bouton1(){ return 0; }
bool COM_Serial::bouton2(){ return 0; }
bool COM_Serial::bouton3(){ return 0; }
bool COM_Serial::bouton4(){ return 0; }
//acc�l�rom�tre
int COM_Serial::cast(){ return 0; }
//encodeur
int COM_Serial::encodeur(){ return 0; }

bool COM_Serial::isConnected() { return connected; }

bool COM_Serial::writeMSG(const json &j_msg){
    if (!connected) return false;

    string payload = j_msg.dump();
    DWORD bytesWritten;
    bool result = WriteFile(hSerial, payload.c_str(), (DWORD)payload.length(), &bytesWritten, NULL);

    return result && (bytesWritten == payload.length());
}

json COM_Serial::readMSG(){

    if (!connected) return json();

    char buffer[256]; // Augment� un peu pour plus de s�curit�
    DWORD bytesRead;
    json j_rcv;

    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            try {
                j_rcv = json::parse(buffer);
            }
            catch (json::parse_error& e) {
                // Si ce n'est pas du JSON valide, on peut retourner le texte brut ou logger l'erreur
                cerr << "Erreur de parsing JSON : " << e.what() << endl;
            }
        }
    }
    return j_rcv;
}