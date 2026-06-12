#pragma once
#include "Config.hpp"
#include "HomeManager.hpp"
#include <string>

// Klasa odpowiedzialna za binarn¹ serializacjê danych systemu smart home.
// Umo¿liwia trwa³e zapisywanie oraz odtwarzanie pe³nego stanu obiektów w pliku zewnêtrznym.

class SMARTHOME_API BinarySerializer {
public:
    BinarySerializer() = default;
    ~BinarySerializer() = default;

    // Metoda eksportuj¹ca kolekcjê urz¹dzeñ z mened¿era do pliku binarnego.
    void saveToFile(const HomeManager& manager, const std::string& filename);

    // Metoda importuj¹ca strukturê urz¹dzeñ z pliku binarnego i odbudowuj¹ca stan systemu.
    void loadFromFile(HomeManager& manager, const std::string& filename);
};