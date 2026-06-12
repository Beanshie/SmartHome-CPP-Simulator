#pragma once
#include "SmartDevice.hpp"

// Klasa reprezentuj¹ca inteligentne oœwietlenie (¿arówkê).
// Rozszerza podstawowe urz¹dzenie o parametryzacjê poziomu jasnoœci w strumieniu procentowym.

class SMARTHOME_API SmartLight : public SmartDevice {
private:
    int brightness; // Dodatkowa cecha tylko dla ¿arówki (0-100%)

public:
    SmartLight(std::string name);

    // Nadpisany destruktor wirtualny gwarantuj¹cy poprawne zwalnianie zasobów podklasy.
    ~SmartLight() override = default;

    // Nadpisane metody polimorficzne zarz¹dzaj¹ce stanem zasilania oœwietlenia.
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Zmiana natê¿enia œwiat³a wraz z automatyczn¹ walidacj¹ poprawnoœci zakresu.
    void setBrightness(int level);

    // Pobranie aktualnego poziomu jasnoœci zapisanego w pamiêci urz¹dzenia.
    int getBrightness() const;

    // Wygenerowanie linii statusowej oœwietlenia przeznaczonej dla g³ównego menu interfejsu.
    std::string getDashboardInfo() const override;
};