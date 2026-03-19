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
public:
    // Constructeur : Ouvre et configure le port
    COM_Serial(string port, DWORD baudRate = CBR_115200);
    ~COM_Serial();

    //joystick
    int joystickPotX();
    int joystickPotY();
    //bouton
    bool bouton1();
    bool bouton2();
    bool bouton3();
    bool bouton4();
    //acc�l�rom�tre
    int cast();
    //encodeur
    int encodeur();
    //Lecture et �criture du jsom
    bool isConnected();
    bool writeMSG(const json& j_msg);
    json readMSG();
    json askMSG();

};
#endif
