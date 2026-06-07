#pragma once
#include "SmartDevice.hpp"

class SMARTHOME_API Thermostat : public SmartDevice {
private:
    double target_temperature; // Docelowa temperatura

public:
    Thermostat(std::string name);
    ~Thermostat() override = default;

    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    void setTemperature(double temp);
    double getTemperature() const;
};