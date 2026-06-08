#include "BinarySerializer.hpp"
#include "SmartHomeException.hpp"
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"
#include <fstream>
#include <iostream>

void BinarySerializer::saveToFile(const HomeManager& manager, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::out);

    if (!out.is_open()) {
        throw SmartHomeException("Blad zapisu: Nie mozna otworzyc pliku " + filename);
    }

    const auto& devices = manager.getDevices();

    size_t count = devices.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& device : devices) {
        int type_id = 0;

        if (dynamic_cast<SmartLight*>(device.get())) type_id = 1;
        else if (dynamic_cast<Thermostat*>(device.get())) type_id = 2;
        else if (dynamic_cast<SecurityCamera*>(device.get())) type_id = 3;
        else if (dynamic_cast<SmartLock*>(device.get())) type_id = 4;

        out.write(reinterpret_cast<const char*>(&type_id), sizeof(type_id));

        std::string name = device->getName();
        size_t name_len = name.length();
        out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        out.write(name.c_str(), name_len);

        bool is_on = device->isOn();
        out.write(reinterpret_cast<const char*>(&is_on), sizeof(is_on));

        if (type_id == 4) {
            auto* lock = dynamic_cast<SmartLock*>(device.get());
            bool is_locked = lock->isLocked();
            out.write(reinterpret_cast<const char*>(&is_locked), sizeof(is_locked));

            std::string pin = lock->getPinCode();
            size_t pin_len = pin.length();
            out.write(reinterpret_cast<const char*>(&pin_len), sizeof(pin_len));
            out.write(pin.c_str(), pin_len);
        }
    }

    out.close();
    std::cout << "[System] Zapisano konfiguracje do pliku: " << filename << "\n";
}

void BinarySerializer::loadFromFile(HomeManager& manager, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::in);

    if (!in.is_open()) {
        std::cout << "[System] Brak pliku " << filename << ". Rozpoczynanie z czysta konfiguracja.\n";
        return;
    }

    size_t count = 0;
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count))) return;

    for (size_t i = 0; i < count; ++i) {
        int type_id;
        in.read(reinterpret_cast<char*>(&type_id), sizeof(type_id));

        size_t name_len;
        in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));

        std::string name(name_len, '\0');
        in.read(&name[0], name_len);

        bool is_on;
        in.read(reinterpret_cast<char*>(&is_on), sizeof(is_on));

        bool lock_is_locked = true;
        std::string lock_pin = "1234";

        if (type_id == 4) {
            in.read(reinterpret_cast<char*>(&lock_is_locked), sizeof(lock_is_locked));

            size_t pin_len;
            in.read(reinterpret_cast<char*>(&pin_len), sizeof(pin_len));
            lock_pin.resize(pin_len);
            in.read(&lock_pin[0], pin_len);
        }

        std::unique_ptr<SmartDevice> new_device;
        switch (type_id) {
        case 1: new_device = std::make_unique<SmartLight>(name); break;
        case 2: new_device = std::make_unique<Thermostat>(name); break;
        case 3: new_device = std::make_unique<SecurityCamera>(name); break;
        case 4: new_device = std::make_unique<SmartLock>(name, lock_pin); break;
        default: continue;
        }

        // --- KLUCZOWA ZMIANA ---
        // Ustawiamy status bazowy zamiast wywo³ywaæ metody turnOn/turnOff
        new_device->setStatus(is_on);

        if (type_id == 3 && is_on) {
            auto* cam = dynamic_cast<SecurityCamera*>(new_device.get());
            if (cam) cam->startRecording();
        }

        if (type_id == 4) {
            auto* lock = dynamic_cast<SmartLock*>(new_device.get());
            if (lock) lock->setLockState(lock_is_locked);
        }

        manager.addDevice(std::move(new_device));
    }

    in.close();
    std::cout << "[System] Pomyslnie wczytano " << count << " urzadzen z pliku " << filename << "\n";
}