#pragma once
#include "SmartDevice.hpp"

// Dziedziczenie publiczne po naszej klasie bazowej
class SMARTHOME_API SmartLight : public SmartDevice {
private:
    int brightness; // Dodatkowa cecha tylko dla ¿arówki (0-100%)

public:
    SmartLight(std::string name);

    // Nadpisujemy destruktor
    ~SmartLight() override = default;

    // Wymóg: Override. Kompilator pilnuje, czy na pewno nadpisujemy metody z klasy bazowej.
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Metody specyficzne tylko dla ¿arówki
    void setBrightness(int level);
    int getBrightness() const;
    std::string getDashboardInfo() const override;
};