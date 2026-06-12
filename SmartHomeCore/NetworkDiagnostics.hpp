#pragma once
#include "Config.hpp"
#include "SmartDevice.hpp"
#include <string>

// Klasa narzêdziowa przeznaczona do symulacji diagnostyki sieciowej urz¹dzeñ.
// Wykorzystuje mechanizm przyjaŸni oraz polimorfizm do odczytu zabezpieczonych parametrów sprzêtowych.

class SMARTHOME_API NetworkDiagnostics {
public:
    NetworkDiagnostics() = default;
    ~NetworkDiagnostics() = default;

    // Przeprowadzenie weryfikacji po³¹czenia sieciowego dla dowolnego obiektu klasy pochodnej.
    void checkConnection(const SmartDevice& device);

    // Pobranie i sformatowanie adresu MAC przypisanego do sprawdzanego urz¹dzenia.
    std::string getDeviceMacAddress(const SmartDevice& device);
};