#pragma once
#include "Config.hpp"
#include <string>

// Pusta deklaracja klasy, któr¹ stworzymy w przysz³oœci. 
// Potrzebna, aby móc siê z ni¹ "zaprzyjaŸniæ".
class NetworkDiagnostics;

class SMARTHOME_API SmartDevice {
private:
    // Wymóg: Hermetyzacja (Enkapsulacja). Pola s¹ ukryte przed œwiatem zewnêtrznym.
    std::string name;
    bool is_on;

    // Specjalne, prywatne pole, do którego dostêp bêdzie mia³a TYLKO zaprzyjaŸniona klasa
    std::string secret_mac_address;

public:
    // Konstruktor
    SmartDevice(std::string device_name);

    // Wirtualny destruktor - absolutnie wymagany, gdy u¿ywamy polimorfizmu!
    virtual ~SmartDevice() = default;

    // Wymóg: Polimorfizm (czysto wirtualne metody, oznaczane jako "= 0").
    // Sprawia to, ¿e z tej klasy nie da siê utworzyæ obiektu, jest to czysty interfejs.
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    // Ka¿de urz¹dzenie bêdzie musia³o zwracaæ swój typ (np. "¯arówka", "Kamera")
    virtual std::string getDeviceType() const = 0;

    // Publiczne metody dostêpowe (Gettery i Settery)
    std::string getName() const;
    bool isOn() const;

    // Oznaczamy metodê jako wirtualn¹, by klasy pochodne mog³y j¹ nadpisaæ (Override),
    // jeœli ich w³¹czanie wymaga dodatkowej logiki.
    virtual void setStatus(bool status);

    virtual std::string getDashboardInfo() const = 0;

    // Wymóg: Deklaracja przyjaŸni. 
    // Klasa NetworkDiagnostics bêdzie mog³a odczytaæ nasze prywatne pole secret_mac_address.
    friend class NetworkDiagnostics;
};