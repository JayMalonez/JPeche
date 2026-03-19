#include "Input.h"
#include  "Lib/json.hpp"
#include "InputConfig.h"


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

    json message = askMSG();
    return message["pot_X"];
 }

int COM_Serial::joystickPotY(){

    json message = askMSG();
    return message["pot_Y"];
 }

//bouton
bool COM_Serial::bouton1(){

    json message = askMSG();
    return message["BTN_1"] != 0;
    
 }

bool COM_Serial::bouton2(){
    
    json message = askMSG();
    return message["BTN_2"] != 0;
}

bool COM_Serial::bouton3(){ 

    json message = askMSG();
    return message["BTN_3"] != 0;
}

bool COM_Serial::bouton4(){ 

    json message = askMSG();
    return message["BTN_4"] != 0;
 }

//acc�l�rom�tre
int COM_Serial::cast(){

    InputConfig config = InputConfigManager::load();
    json message = askMSG();
    int x = message["X_mG"];
    int y = message["Y_mG"];
    int z = message["Z_mG"];
    int t = x + y + z;
    if ( t > config.ms)
        return 1;

    else
        return 0;

}
//encodeur
int COM_Serial::encodeur(){ 
    InputConfig config = InputConfigManager::load();
    json message = askMSG();
	
    cout << "DEBUG ENCODEUR : " << message["ENCODER"] - enc << endl;
    cout << "DEBUG enc : " << enc << endl;


    if ((message["ENCODER"] - enc) > config.encoderThreshold) {
        enc = message["ENCODER"];
        return 1;
    }
    else if ((message["ENCODER"] - enc) < -config.encoderThreshold) {
        enc = message["ENCODER"];
        return -1;
    }

    else {
        return 0;
	}
}

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

    static std::string accumulateur = "";

    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            accumulateur += buffer;

            size_t pos;
            while ((pos = accumulateur.find('\n')) != std::string::npos) {
                std::string ligneComplete = accumulateur.substr(0, pos);
                
                accumulateur.erase(0, pos + 1);

                if (!ligneComplete.empty() && ligneComplete.back() == '\r') {
                    ligneComplete.pop_back();
                }

                try {
                    size_t startPos = ligneComplete.find('{');
                    if (startPos != std::string::npos) {
                        std::string jsonSeul = ligneComplete.substr(startPos);
                         //cout << "DEBUG PARSING : |" << jsonSeul << "|" << endl;

                        j_rcv = json::parse(jsonSeul);
                        return j_rcv;
                    }
                }
                catch (json::parse_error& e) {
                    cout << "DEBUG SERIAL : |deserialize() failed: " << e.what() << "|" << endl;
                }
            }
        }
    }
    return j_rcv;
}

json COM_Serial::askMSG(){
    json ask;
    writeMSG(ask);
    return readMSG();

}