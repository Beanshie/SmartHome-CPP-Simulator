#pragma once
#include "Config.hpp"
#include "SmartDevice.hpp"
#include <vector>
#include <memory>
#include <string>

// Klasa zarz¹dzaj¹ca kolekcj¹ urz¹dzeñ w inteligentnym domu.
// Odpowiada za cykl ¿ycia obiektów, polimorficzne operacje grupowe oraz wyszukiwanie sprzêtu.

class SMARTHOME_API HomeManager {
private:
    // kontener bezpiecznych sprytnych wskaŸników zarz¹dzaj¹cych pamiêci¹ urz¹dzeñ
    std::vector<std::unique_ptr<SmartDevice>> devices;

public:
    HomeManager() = default;
    ~HomeManager() = default;

    // jawne zablokowanie semantyki kopiowania w celu unikniêcia powielania unikalnych zasobów
    HomeManager(const HomeManager&) = delete;
    HomeManager& operator=(const HomeManager&) = delete;

    // Przeniesienie w³asnoœci do nowego obiektu urz¹dzenia i dodanie go do rejestru.
    void addDevice(std::unique_ptr<SmartDevice> device);

    // Usuniêcie urz¹dzenia z kontenera na podstawie unikalnej nazwy identyfikacyjnej.
    void removeDevice(const std::string& name);

    // Polimorficzne masowe zarz¹dzanie zasilaniem wszystkich zarejestrowanych odbiorników.
    void turnAllOn();
    void turnAllOff();

    // Wygenerowanie podsumowania diagnostycznego stanu ca³ej instalacji domowej w konsoli.
    void printAllStatuses() const;

    // Wyszukanie i zwrócenie surowego wskaŸnika do obiektu na podstawie jego nazwy.
    SmartDevice* getDevice(const std::string& name) const;

    // Udostêpnienie referencji do wewnêtrznego kontenera na potrzeby serializacji binarnej.
    const std::vector<std::unique_ptr<SmartDevice>>& getDevices() const;
};