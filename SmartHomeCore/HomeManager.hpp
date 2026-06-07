#pragma once
#include "Config.hpp"
#include "SmartDevice.hpp"
#include <vector>
#include <memory>
#include <string>

class SMARTHOME_API HomeManager {
private:
    // WYMÓG: Memory Management. 
    // unique_ptr gwarantuje bezpieczeñstwo pamiêci (brak wycieków).
    std::vector<std::unique_ptr<SmartDevice>> devices;

public:
    HomeManager() = default;
    ~HomeManager() = default;

    HomeManager(const HomeManager&) = delete;
    HomeManager& operator=(const HomeManager&) = delete;

    // Przekazujemy urz¹dzenie "na w³asnoœæ" mened¿erowi
    void addDevice(std::unique_ptr<SmartDevice> device);

    // Usuwa urz¹dzenie po nazwie. Jeœli nie znajdzie - rzuci wyj¹tek!
    void removeDevice(const std::string& name);

    // Potêga polimorfizmu: w³¹czamy/wy³¹czamy wszystko jedn¹ pêtl¹
    void turnAllOn();
    void turnAllOff();

    // Wypisuje ³adne podsumowanie stanu domu
    void printAllStatuses() const;

    // Zwraca wskaŸnik na konkretne urz¹dzenie (do odczytu/zmiany stanu)
    SmartDevice* getDevice(const std::string& name) const;

    // Metoda pomocnicza, która bardzo przyda nam siê w Fazie 5 przy plikach binarnych
    const std::vector<std::unique_ptr<SmartDevice>>& getDevices() const;
};