#pragma once

#include "lib/json.hpp"
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

struct InputConfig {
    // valeurs par défaut -> modifier input_config.json pour changer les valeurs
    int joystickCenter = 512;
    int joystickDeadzone = 50;
    int joystickMin = 0;
    int joystickMax = 1023;
    int encoderThreshold = 1;
    int encoderCenter = 0;
    int pollIntervalMs = 200;
    int ms = 3;

    int joystickLeftLimit() const { return joystickCenter - joystickDeadzone; }
    int joystickRightLimit() const { return joystickCenter + joystickDeadzone; }
};

class InputConfigManager {
public:
    static InputConfig load(const std::string& filename = "input_config.json");
};
