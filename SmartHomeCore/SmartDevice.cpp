#include "SmartDevice.hpp"

// Implementacja podstawowych metod wirtualnej klasy bazowej SmartDevice.
// Odpowiada za zarz¹dzanie pamiêci¹ podstawowych flag stanu oraz unikalnego adresu sieciowego.

// Konstruktor przypisuj¹cy nazwê obiektu i inicjalizuj¹cy statyczny, ukryty adres MAC.
SmartDevice::SmartDevice(std::string device_name)
    : name(device_name), is_on(false), secret_mac_address("00:1A:2B:3C:4D:5E") {
}

// Funkcja zwracaj¹ca zapisan¹ nazwê identyfikacyjn¹ danego urz¹dzenia.
std::string SmartDevice::getName() const {
    return name;
}

// Funkcja zwracaj¹ca flagê informuj¹c¹, czy urz¹dzenie jest aktualnie w³¹czone.
bool SmartDevice::isOn() const {
    return is_on;
}

// Funkcja modyfikuj¹ca stan zasilania urz¹dzenia bezpoœrednim wpisem logicznym.
void SmartDevice::setStatus(bool status) {
    is_on = status;
}