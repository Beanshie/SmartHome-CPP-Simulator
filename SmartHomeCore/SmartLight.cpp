#include "SmartLight.hpp"

// Konstruktor - wywo³ujemy najpierw konstruktor klasy bazowej (SmartDevice), 
// a potem ustawiamy jasnoœæ domyœlnie na 100%
SmartLight::SmartLight(std::string name)
    : SmartDevice(name), brightness(100) {
}

void SmartLight::turnOn() {
    setStatus(true); // U¿ywamy metody z klasy bazowej
}

void SmartLight::turnOff() {
    setStatus(false);
}

std::string SmartLight::getDeviceType() const {
    return "Inteligentna Zarowka";
}

void SmartLight::setBrightness(int level) {
    // Proste zabezpieczenie przed nieprawid³owymi wartoœciami
    if (level < 10) brightness = 10;
    else if (level > 100) brightness = 100;
    else brightness = level;
}

int SmartLight::getBrightness() const {
    return brightness;
}

std::string SmartLight::getDashboardInfo() const {
    // Jeœli w³¹czona, poka¿e np. "[ON 80%]", w przeciwnym razie "[OFF]"
    return isOn() ? "[ON " + std::to_string(brightness) + "%]" : "[OFF]";
}