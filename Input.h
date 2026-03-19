#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <windows.h>
#include "lib/json.hpp"
#include <string>
#include <vector>
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
    int bouton1();
    int bouton2();
    int bouton3();
    int bouton4();
    //accéléromêtre
    int cast();
    //encodeur
    int encodeur();
    //Lecture et écriture du jsom
    bool isConnected();
    bool writeMSG(const json& j_msg);
    json readMSG();

};
#endif
