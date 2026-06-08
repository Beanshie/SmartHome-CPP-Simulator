#pragma once
#include "Thermostat.hpp"
#include <string>

class ThermostatUI {
private:
    float temp_buffer = 20.0f;       // Zmienna przechowuj¹ca stan suwaka
    bool is_first_render = true;     // ¯eby zaci¹gn¹æ pocz¹tkow¹ temperaturê z Core'a
    std::string error_message = "";

public:
    void render(Thermostat* therm);
    void reset();
};