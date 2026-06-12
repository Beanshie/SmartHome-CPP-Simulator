#include "HomeManager.hpp"
#include "SmartHomeException.hpp"
#include <iostream>
#include <algorithm>

// Implementacja mened¿era urz¹dzeñ (HomeManager).
// Realizuje operacje na kontenerze sprytnych wskaŸników, automatyzuje masowe 
// zarz¹dzanie zasilaniem i realizuje polimorficzne przeszukiwanie zasobów.

// Funkcja dodaj¹ca nowe urz¹dzenie i przejmuj¹ca nad nim pe³n¹ kontrolê alokacji.
void HomeManager::addDevice(std::unique_ptr<SmartDevice> device) {
    if (device) {
        // transfer w³asnoœci niekopiowalnego zasobu przy u¿yciu semantyki przeniesienia
        devices.push_back(std::move(device));
    }
}

// Funkcja usuwaj¹ca urz¹dzenie z bazy po nazwie lub rzucaj¹ca wyj¹tek w przypadku braku trafienia.
void HomeManager::removeDevice(const std::string& name) {
    // idiom erase-remove przy u¿yciu wyra¿enia lambda do identyfikacji obiektów
    auto it = std::remove_if(devices.begin(), devices.end(),
        [&name](const std::unique_ptr<SmartDevice>& d) {
            return d->getName() == name;
        });

    if (it != devices.end()) {
        devices.erase(it, devices.end());
        std::cout << "[HomeManager] Usunieto urzadzenie: " << name << "\n";
    }
    else {
        // wywo³anie dedykowanego b³êdu dziedzinowego aplikacji
        throw SmartHomeException("Blad usuwania: Nie znaleziono urzadzenia '" + name + "'!");
    }
}

// Funkcja masowo aktywuj¹ca zasilanie dla wszystkich posiadanych obiektów.
void HomeManager::turnAllOn() {
    for (auto& device : devices) {
        // polimorficzne wywo³anie metody wirtualnej turnOn()
        device->turnOn();
    }
}

// Funkcja masowo odcinaj¹ca zasilanie od wszystkich posiadanych obiektów.
void HomeManager::turnAllOff() {
    for (auto& device : devices) {
        device->turnOff();
    }
}

// Funkcja zrzucaj¹ca tekstowy raport diagnostyczny urz¹dzeñ na strumieñ wyjœciowy konsoli.
void HomeManager::printAllStatuses() const {
    std::cout << "--- Status Domu (" << devices.size() << " urzadzen) ---\n";
    for (const auto& device : devices) {
        std::cout << "- " << device->getName() << " [" << device->getDeviceType() << "] : "
            << (device->isOn() ? "Wlaczony" : "Wylaczony") << "\n";
    }
    std::cout << "--------------------------------------\n";
}

// Funkcja wyszukuj¹ca obiekt po unikalnym kluczu tekstowym i zwracaj¹ca jego surowy wskaŸnik.
SmartDevice* HomeManager::getDevice(const std::string& name) const {
    for (const auto& device : devices) {
        if (device->getName() == name) {
            // bezpieczne podejrzenie adresu zarz¹dzanego bez zrzekania siê w³asnoœci unique_ptr
            return device.get();
        }
    }
    throw SmartHomeException("Blad wyszukiwania: Urzadzenie '" + name + "' nie istnieje!");
}

// Funkcja daj¹ca bezpieczny wgl¹d (tylko do odczytu) w strukturê wewnêtrzn¹ wektora.
const std::vector<std::unique_ptr<SmartDevice>>& HomeManager::getDevices() const {
    return devices;
}