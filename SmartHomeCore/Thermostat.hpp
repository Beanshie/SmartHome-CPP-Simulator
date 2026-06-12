#pragma once
#include "SmartDevice.hpp"

// Klasa reprezentuj¹ca inteligentny termostat pokojowy.
// Rozszerza interfejs bazowy o precyzyjn¹ regulacjê i odczyt zadanej temperatury docelowej.

class SMARTHOME_API Thermostat : public SmartDevice {
private:
    double target_temperature; // Docelowa temperatura

public:
    Thermostat(std::string name);
    ~Thermostat() override = default;

    // Nadpisane metody polimorficzne zarz¹dzaj¹ce stanem aktywnoœci termostatu.
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Zmiana docelowej temperatury grzania wraz z walidacj¹ dopuszczalnych progów.
    void setTemperature(double temp);

    // Pobranie aktualnie ustawionej wartoœci temperatury z pamiêci urz¹dzenia.
    double getTemperature() const;

    // Wygenerowanie sformatowanej linii statusu z temperatur¹ na potrzeby g³ównego panelu GUI.
    std::string getDashboardInfo() const override;
};