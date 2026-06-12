#pragma once
#include "Config.hpp"
#include <exception>
#include <string>

// Klasa dedykowanego wyj¹tku dla b³êdów dziedzinowych systemu inteligentnego domu.
// Dziedziczy po std::exception, umo¿liwiaj¹c standaryzowan¹ obs³ugê b³êdów w blokach try-catch.

class SMARTHOME_API SmartHomeException : public std::exception {
protected:
    std::string message;

public:
    // Konstruktor jawny tworz¹cy wyj¹tek na podstawie przekazanego komunikatu tekstowego.
    explicit SmartHomeException(const std::string& msg);

    // Nadpisana polimorficzna metoda zwracaj¹ca surowy wskaŸnik do ³añcucha znaków b³êdu.
    const char* what() const noexcept override;
};