#pragma once
#include "Config.hpp"
#include <string>

// Pusta deklaracja wyprzedzaj¹ca klasy diagnostycznej na potrzeby relacji przyjaŸni.
class NetworkDiagnostics;

// Abstrakcyjna klasa bazowa definiuj¹ca wspólny interfejs dla wszystkich urz¹dzeñ inteligentnych.
// Wymusza hermetyzacjê danych oraz implementacjê polimorficznych metod zarz¹dzania stanem.

class SMARTHOME_API SmartDevice {
private:
    std::string name;
    bool is_on;

    // unikalny identyfikator sprzêtowy ukryty przed œwiatem zewnêtrznym i klasami pochodnymi
    std::string secret_mac_address;

public:
    // Konstruktor inicjalizuj¹cy nazwê urz¹dzenia oraz generuj¹cy unikalny adres MAC.
    SmartDevice(std::string device_name);

    // Wirtualny destruktor gwarantuj¹cy prawid³owe zwalnianie pamiêci obiektów klas pochodnych.
    virtual ~SmartDevice() = default;

    // Czysto wirtualne metody polimorficzne definiuj¹ce cykl zasilania sprzêtu.
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    // Zwrócenie tekstowego identyfikatora okreœlaj¹cego podtyp urz¹dzenia.
    virtual std::string getDeviceType() const = 0;

    // Publiczne metody dostêpowe do odczytu podstawowych w³aœciwoœci obiektu.
    std::string getName() const;
    bool isOn() const;

    // Wirtualny setter umo¿liwiaj¹cy rozszerzenie logiki zmiany zasilania w klasach pochodnych.
    virtual void setStatus(bool status);

    // Zwrócenie sformatowanej linii statusu przeznaczonej do g³ównego widgetu listy GUI.
    virtual std::string getDashboardInfo() const = 0;

    // Deklaracja przyjaŸni umo¿liwiaj¹ca zewnêtrznej klasie wgl¹d w prywatne pole adresu MAC.
    friend class NetworkDiagnostics;
};