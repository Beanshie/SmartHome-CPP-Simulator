#include "SmartDevice.hpp"

// Implementacja konstruktora
// Generujemy prosty fa³szywy adres MAC dla celów demonstracyjnych przyjaŸni klas
SmartDevice::SmartDevice(std::string device_name)
    : name(device_name), is_on(false), secret_mac_address("00:1A:2B:3C:4D:5E") {
}

std::string SmartDevice::getName() const {
    return name;
}

bool SmartDevice::isOn() const {
    return is_on;
}

void SmartDevice::setStatus(bool status) {
    is_on = status;
}