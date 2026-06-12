#pragma once
#include "SmartDevice.hpp"
#include <string>

// Klasa reprezentuj¹ca inteligentny zamek elektroniczny (SmartLock).
// Rozszerza interfejs bazowy o autoryzacjê kodem PIN, ryglowanie oraz metody eksportu stanu dla serializatora.

class SMARTHOME_API SmartLock : public SmartDevice {
private:
    bool is_locked;
    std::string pin_code;

public:
    SmartLock(std::string name, std::string pin);
    ~SmartLock() override = default;

    // Nadpisane metody polimorficzne zarz¹dzaj¹ce stanem czuwania elektroniki zamka.
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Natychmiastowe zablokowanie rygla zamka bez weryfikacji autoryzacyjnej.
    void lock();

    // Próba odblokowania zamka przy u¿yciu kodu PIN (rzuca wyj¹tek w przypadku b³êdu).
    void unlock(std::string entered_pin);

    // Sprawdzenie, czy rygiel zamka jest aktualnie w pozycji zablokowanej.
    bool isLocked() const;

    // Pobranie zakodowanego ci¹gu PIN na potrzeby zapisu binarnego.
    std::string getPinCode() const;

    // Bezpoœrednie wymuszenie stanu blokady podczas odtwarzania danych z pliku binarnego.
    void setLockState(bool state);

    // Wygenerowanie dedykowanego statusu blokady zamka dla g³ównego pulpitu GUI.
    std::string getDashboardInfo() const override;
};