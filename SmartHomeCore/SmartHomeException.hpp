#pragma once
#include "Config.hpp"
#include <exception>
#include <string>

// Nasza klasa dziedziczy po standardowym wyj¹tku C++ (std::exception)
class SMARTHOME_API SmartHomeException : public std::exception {
protected:
    std::string message;

public:
    // Konstruktor przyjmuj¹cy treœæ b³êdu
    explicit SmartHomeException(const std::string& msg);

    // Nadpisujemy wirtualn¹ metodê what(), aby zwraca³a nasz komunikat.
    // S³ówko 'noexcept' oznacza, ¿e ta metoda sama w sobie nigdy nie rzuci wyj¹tku.
    const char* what() const noexcept override;
};