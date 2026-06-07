#include "NetworkDiagnostics.hpp"
#include <iostream>

void NetworkDiagnostics::checkConnection(const SmartDevice& device) {
    // MAGIA PRZYJAèNI: 
    // Odwo≥ujemy siÍ do device.secret_mac_address. 
    // Gdyby ta klasa nie by≥a 'friend', kompilator wyrzuci≥by tutaj b≥πd,
    // øe prÛbujemy dotknπÊ prywatnego pola.

    std::cout << "[Diagnostyka] Pingowanie urzadzenia '" << device.getName()
        << "' pod ukrytym adresem MAC: " << device.secret_mac_address << "...\n";

    std::cout << "[Diagnostyka] Odpowiedz z " << device.secret_mac_address
        << ": bajtow=32 czas=15ms TTL=64 (Polaczenie stabilne)\n";
}

std::string NetworkDiagnostics::getDeviceMacAddress(const SmartDevice& device) {
    // Ponownie, swobodny dostÍp do prywatnego pola
    return device.secret_mac_address;
}