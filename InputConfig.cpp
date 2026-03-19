#include "InputConfig.h"

InputConfig InputConfigManager::load(const std::string& filename) {
    InputConfig config;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: cannot open " << filename << ", using defaults" << std::endl;
        return config;
    }

    try {
        json j;
        file >> j;

        if (j.contains("joystickCenter")) config.joystickCenter = j["joystickCenter"].get<int>();
        if (j.contains("joystickDeadzone")) config.joystickDeadzone = j["joystickDeadzone"].get<int>();
        if (j.contains("joystickMin")) config.joystickMin = j["joystickMin"].get<int>();
        if (j.contains("joystickMax")) config.joystickMax = j["joystickMax"].get<int>();
        if (j.contains("encoderThreshold")) config.encoderThreshold = j["encoderThreshold"].get<int>();
        if (j.contains("encoderCenter")) config.encoderCenter = j["encoderCenter"].get<int>();
        if (j.contains("pollIntervalMs")) config.pollIntervalMs = j["pollIntervalMs"].get<int>();
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing " << filename << ": " << e.what() << ". Using defaults." << std::endl;
    }

    return config;
}
