#include "BinarySerializer.hpp"
#include "SmartHomeException.hpp"
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"
#include <fstream>
#include <iostream>

void BinarySerializer::saveToFile(const HomeManager& manager, const std::string& filename) {
    // Otwieramy plik do zapisu (out) w trybie binarnym (binary)
    std::ofstream out(filename, std::ios::binary | std::ios::out);

    if (!out.is_open()) {
        throw SmartHomeException("Blad zapisu: Nie mozna otworzyc pliku " + filename);
    }

    const auto& devices = manager.getDevices();

    // 1. Zapisujemy liczbê urz¹dzeñ
    size_t count = devices.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    // 2. Zapisujemy ka¿de urz¹dzenie po kolei
    for (const auto& device : devices) {
        int type_id = 0; // 1: Lampa, 2: Termostat, 3: Kamera, 4: Zamek

        // Rozpoznawanie typu w czasie rzeczywistym
        if (dynamic_cast<SmartLight*>(device.get())) type_id = 1;
        else if (dynamic_cast<Thermostat*>(device.get())) type_id = 2;
        else if (dynamic_cast<SecurityCamera*>(device.get())) type_id = 3;
        else if (dynamic_cast<SmartLock*>(device.get())) type_id = 4;

        // Zapisujemy typ
        out.write(reinterpret_cast<const char*>(&type_id), sizeof(type_id));

        // Zapisujemy d³ugoœæ nazwy i sam¹ nazwê (stringi w plikach binarnych wymagaj¹ d³ugoœci)
        std::string name = device->getName();
        size_t name_len = name.length();
        out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        out.write(name.c_str(), name_len);

        // Zapisujemy stan w³¹cz/wy³¹cz
        bool is_on = device->isOn();
        out.write(reinterpret_cast<const char*>(&is_on), sizeof(is_on));
    }

    out.close();
    std::cout << "[System] Zapisano konfiguracje do pliku: " << filename << "\n";
}

void BinarySerializer::loadFromFile(HomeManager& manager, const std::string& filename) {
    // Otwieramy plik do odczytu (in) w trybie binarnym (binary)
    std::ifstream in(filename, std::ios::binary | std::ios::in);

    if (!in.is_open()) {
        std::cout << "[System] Brak pliku " << filename << ". Rozpoczynanie z czysta konfiguracja.\n";
        return;
    }

    size_t count = 0;
    // Odczytujemy liczbê urz¹dzeñ
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

        // Odtwarzanie urz¹dzeñ na podstawie typu
        std::unique_ptr<SmartDevice> new_device;
        switch (type_id) {
        case 1: new_device = std::make_unique<SmartLight>(name); break;
        case 2: new_device = std::make_unique<Thermostat>(name); break;
        case 3: new_device = std::make_unique<SecurityCamera>(name); break;
        case 4: new_device = std::make_unique<SmartLock>(name, "1234"); break; // Domyœlny PIN przy odtwarzaniu
        default: continue; // Nieznany typ
        }

        // Przywracanie stanu
        if (is_on) new_device->turnOn();
        else new_device->turnOff();

        manager.addDevice(std::move(new_device));
    }

    in.close();
    std::cout << "[System] Pomyslnie wczytano " << count << " urzadzen z pliku " << filename << "\n";
}