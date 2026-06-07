#pragma once
#include "Config.hpp"
#include "HomeManager.hpp"
#include <string>

class SMARTHOME_API BinarySerializer {
public:
    BinarySerializer() = default;
    ~BinarySerializer() = default;

    // Metoda zapisuj¹ca stan domu do pliku binarnego
    void saveToFile(const HomeManager& manager, const std::string& filename);

    // Metoda wczytuj¹ca stan z pliku binarnego do mened¿era
    void loadFromFile(HomeManager& manager, const std::string& filename);
};