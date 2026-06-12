#include "NetworkDiagnostics.hpp"
#include <iostream>

// Implementacja modu³u diagnostyki sieciowej instalacji inteligentnego domu.
// Wykorzystuje deklaracjê przyjaŸni do odczytu prywatnych, sprzêtowych adresów MAC urz¹dzeñ.

// Funkcja symuluj¹ca procedurê testowania po³¹czenia sieciowego (ping) przy u¿yciu ukrytego adresu MAC.
void NetworkDiagnostics::checkConnection(const SmartDevice& device) {
    // bezpoœredni odczyt pola prywatnego innej klasy dziêki relacji friend class
    std::cout << "[Diagnostyka] Pingowanie urzadzenia '" << device.getName()
        << "' pod ukrytym adresem MAC: " << device.secret_mac_address << "...\n";

    std::cout << "[Diagnostyka] Odpowiedz z " << device.secret_mac_address
        << ": bajtow=32 czas=15ms TTL=64 (Polaczenie stabilne)\n";
}

// Funkcja pobieraj¹ca i zwracaj¹ca zabezpieczony adres MAC sprawdzanego obiektu.
std::string NetworkDiagnostics::getDeviceMacAddress(const SmartDevice& device) {
    // bezpieczne przekazanie chronionej wartoœci do wy¿szych warstw aplikacji (np. interfejsu GUI)
    return device.secret_mac_address;
}