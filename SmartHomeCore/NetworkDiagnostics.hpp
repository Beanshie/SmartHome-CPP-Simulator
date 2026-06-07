#pragma once
#include "Config.hpp"
#include "SmartDevice.hpp"
#include <string>

class SMARTHOME_API NetworkDiagnostics {
public:
    NetworkDiagnostics() = default;
    ~NetworkDiagnostics() = default;

    // Metoda, która przyjmuje referencjê do dowolnego urz¹dzenia.
    // Dziêki polimorfizmowi mo¿emy tu przekazaæ ¿arówkê, termostat, zamek, cokolwiek!
    void checkConnection(const SmartDevice& device);

    // Zwraca ukryty adres MAC
    std::string getDeviceMacAddress(const SmartDevice& device);
};