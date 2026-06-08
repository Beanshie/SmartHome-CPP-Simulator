#include "SmartLock.hpp"
#include "SmartHomeException.hpp"

SmartLock::SmartLock(std::string name, std::string pin)
    : SmartDevice(name), is_locked(true), pin_code(pin) {
    // Zamek domyœlnie jest w³¹czony (aktywny) i zablokowany
    setStatus(true);
}

void SmartLock::turnOn() {
    setStatus(true);
    lock();
}

void SmartLock::turnOff() {
    setStatus(false);
    is_locked = false; // Ca³kowite wy³¹czenie zamka odryglowuje drzwi
}

std::string SmartLock::getDeviceType() const {
    return "Inteligentny Zamek";
}

void SmartLock::lock() {
    is_locked = true;
}

void SmartLock::unlock(std::string entered_pin) {
    if (!isOn()) {
        throw SmartHomeException("B³¹d: Zamek " + getName() + " jest wy³¹czony z pr¹du!");
    }

    if (entered_pin == pin_code) {
        is_locked = false;
    }
    else {
        // Wykorzystanie wyj¹tku przy b³êdnym PIN-ie
        throw SmartHomeException("ALARM! Podano b³êdny kod PIN dla zamka: " + getName());
    }
}

bool SmartLock::isLocked() const {
    return is_locked;
}

// --- NOWE METODY DLA SERIALIZATORA ---
std::string SmartLock::getPinCode() const {
    return pin_code;
}

void SmartLock::setLockState(bool state) {
    is_locked = state;
}

std::string SmartLock::getDashboardInfo() const {
    return isLocked() ? "[ZAMKNIETY]" : "[OTWARTY]";
}