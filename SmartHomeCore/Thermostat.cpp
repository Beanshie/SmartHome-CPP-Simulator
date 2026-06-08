#include "Thermostat.hpp"
#include "SmartHomeException.hpp" // Musimy do³¹czyæ nasz wyj¹tek!
#include <string>

Thermostat::Thermostat(std::string name)
    : SmartDevice(name), target_temperature(21.0) {
}

void Thermostat::turnOn() {
    setStatus(true);
}

void Thermostat::turnOff() {
    setStatus(false);
}

std::string Thermostat::getDeviceType() const {
    return "Termostat";
}

void Thermostat::setTemperature(double temp) {
    // Wykorzystanie wymagañ: Rzucamy wyj¹tek, jeœli ktoœ zaszaleje z temperatur¹!
    if (temp < 10.0 || temp > 40.0) {
        throw SmartHomeException("B³¹d! Temperatura " + std::to_string(temp) + "C jest poza bezpiecznym zakresem (10-40C).");
    }
    target_temperature = temp;
}

double Thermostat::getTemperature() const {
    return target_temperature;
}

std::string Thermostat::getDashboardInfo() const {
    return std::to_string((int)target_temperature) + " C";
}