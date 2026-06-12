#include "Thermostat.hpp"
#include "SmartHomeException.hpp"
#include <string>

// Implementacja zachowañ oraz walidacji progów termicznych dla inteligentnego termostatu.
// Zapewnia ochronê przed ustawieniem skrajnych wartoœci temperatur przy u¿yciu mechanizmu wyj¹tków.

// Konstruktor klasy pochodnej definiuj¹cy fabryczn¹ wartoœæ temperatury docelowej.
Thermostat::Thermostat(std::string name)
    : SmartDevice(name), target_temperature(21.0) {
}

// Funkcja aktywuj¹ca zasilanie termostatu poprzez wywo³anie metody klasy nadrzêdnej.
void Thermostat::turnOn() {
    setStatus(true);
}

// Funkcja odcinaj¹ca zasilanie termostatu i zawieszaj¹ca kontrolê nad temperatur¹.
void Thermostat::turnOff() {
    setStatus(false);
}

// Funkcja zwracaj¹ca sta³y identyfikator tekstowy podtypu urz¹dzenia dla celów polimorficznych.
std::string Thermostat::getDeviceType() const {
    return "Termostat";
}

// Funkcja modyfikuj¹ca docelow¹ temperaturê grzania z rygorystyczn¹ kontrol¹ bezpiecznego zakresu 10-40°C.
void Thermostat::setTemperature(double temp) {
    if (temp < 10.0 || temp > 40.0) {
        // zg³oszenie b³êdu walidacji w przypadku przekroczenia dopuszczalnych limitów fizycznych
        throw SmartHomeException("B³¹d! Temperatura " + std::to_string(temp) + "C jest poza bezpiecznym zakresem (10-40C).");
    }
    target_temperature = temp;
}

// Funkcja zwracaj¹ca aktualnie zapisan¹ w urz¹dzeniu temperaturê docelow¹.
double Thermostat::getTemperature() const {
    return target_temperature;
}

// Funkcja generuj¹ca tekstowy opis temperatury przeznaczony do wyœwietlenia na liœcie g³ównej GUI.
std::string Thermostat::getDashboardInfo() const {
    return std::to_string((int)target_temperature) + " C";
}