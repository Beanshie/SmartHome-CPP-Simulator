#include "HomeManager.hpp"
#include "SmartHomeException.hpp"
#include <iostream>
#include <algorithm> // Do std::remove_if

void HomeManager::addDevice(std::unique_ptr<SmartDevice> device) {
    if (device) {
        // std::move jest konieczne, bo unique_ptr nie da siê skopiowaæ
        devices.push_back(std::move(device));
    }
}

void HomeManager::removeDevice(const std::string& name) {
    // Szukamy urz¹dzenia po nazwie przy u¿yciu biblioteki algorytmów
    auto it = std::remove_if(devices.begin(), devices.end(),
        [&name](const std::unique_ptr<SmartDevice>& d) {
            return d->getName() == name;
        });

    // Jeœli znaleŸliœmy i przesunêliœmy, to usuwamy
    if (it != devices.end()) {
        devices.erase(it, devices.end());
        std::cout << "[HomeManager] Usunieto urzadzenie: " << name << "\n";
    }
    else {
        // U¿ycie naszego wyj¹tku
        throw SmartHomeException("Blad usuwania: Nie znaleziono urzadzenia '" + name + "'!");
    }
}

void HomeManager::turnAllOn() {
    for (auto& device : devices) {
        device->turnOn(); // Kompilator sam dobierze odpowiednie w³¹czanie (override)
    }
}

void HomeManager::turnAllOff() {
    for (auto& device : devices) {
        device->turnOff();
    }
}

void HomeManager::printAllStatuses() const {
    std::cout << "--- Status Domu (" << devices.size() << " urzadzen) ---\n";
    for (const auto& device : devices) {
        std::cout << "- " << device->getName() << " [" << device->getDeviceType() << "] : "
            << (device->isOn() ? "Wlaczony" : "Wylaczony") << "\n";
    }
    std::cout << "--------------------------------------\n";
}

SmartDevice* HomeManager::getDevice(const std::string& name) const {
    for (const auto& device : devices) {
        if (device->getName() == name) {
            return device.get(); // Zwracamy tzw. "surowy wskaŸnik" (raw pointer) tylko do u¿ycia
        }
    }
    throw SmartHomeException("Blad wyszukiwania: Urzadzenie '" + name + "' nie istnieje!");
}

const std::vector<std::unique_ptr<SmartDevice>>& HomeManager::getDevices() const {
    return devices;
}