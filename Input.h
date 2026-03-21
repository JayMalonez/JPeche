#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <windows.h>
#include "lib/json.hpp"
#include <vector>
#include "InputConfig.h"

using namespace std;
using json = nlohmann::json;

class COM_Serial {
private:
    HANDLE hSerial;
    string portName;
    bool connected;
    string message_buffer;
    
	int enc = 0; // Variable pour stocker la dernière valeur de l'encodeur
    json data;
public:
    // Constructeur : Ouvre et configure le port
    COM_Serial(string port, DWORD baudRate = CBR_115200);
    ~COM_Serial();

    bool isConnected();

    //Lecture et ecriture du json
    bool writeMSG(const json& j_msg);
    json readMSG();
    void askMSG(); //update le data

    //retourne les valeurs du data
    int joystickPotX();
    int joystickPotY();
    bool bouton1();
    bool bouton2();
    bool bouton3();
    bool bouton4();
    int cast();
    int encodeur();

};
#endif
