#pragma once
#include "Thermostat.hpp"
#include <string>

// widok dla termostatu. odpowiada za wyswietlanie suwaka do temperatury 
// i komunikowanie sie z obiektem logicznym.
class ThermostatUI {
private:
    // bufor na stan suwaka w imgui
    float temp_buffer = 20.0f;

    // flaga zeby pobrac aktualna temperature z urzadzenia tylko raz na starcie
    bool is_first_render = true;
    std::string error_message = "";

public:
    void render(Thermostat* therm);

    // reset flagi i bledow przy wyjsciu z panelu
    void reset();
};