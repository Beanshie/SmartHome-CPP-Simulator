#include "SmartLock.hpp"
#include "SmartHomeException.hpp"

// Implementacja zachowañ oraz logiki autoryzacji dla elektronicznego zamka drzwi.
// Realizuje zabezpieczenia dostêpowe przy u¿yciu kodu PIN oraz obs³uguje mechanizmy kontroli rygla.

// Konstruktor klasy pochodnej ustawiaj¹cy kod autoryzacji i domyœlny stan ryglowania.
SmartLock::SmartLock(std::string name, std::string pin)
    : SmartDevice(name), is_locked(true), pin_code(pin) {
    setStatus(true);
}

// Funkcja aktywuj¹ca system bezpieczeñstwa zamka i automatycznie rygluj¹ca drzwi.
void SmartLock::turnOn() {
    setStatus(true);
    lock();
}

// Funkcja wy³¹czaj¹ca zasilanie modu³u elektronicznego, co skutkuje awaryjnym odryglowaniem rygla.
void SmartLock::turnOff() {
    setStatus(false);
    is_locked = false;
}

// Funkcja zwracaj¹ca sta³y identyfikator tekstowy podtypu urz¹dzenia dla celów polimorficznych.
std::string SmartLock::getDeviceType() const {
    return "Inteligentny Zamek";
}

// Funkcja wymuszaj¹ca przejœcie rygla mechanicznego w pozycjê zablokowan¹.
void SmartLock::lock() {
    is_locked = true;
}

// Funkcja weryfikuj¹ca poprawnoœæ kodu PIN i zdejmuj¹ca blokadê lub zg³aszaj¹ca b³¹d w formie wyj¹tku.
void SmartLock::unlock(std::string entered_pin) {
    if (!isOn()) {
        throw SmartHomeException("B³¹d: Zamek " + getName() + " jest wy³¹czony z pr¹du!");
    }

    if (entered_pin == pin_code) {
        is_locked = false;
    }
    else {
        // rzucenie wyj¹tku dziedzinowego w przypadku niezgodnoœci buforów kodu pin
        throw SmartHomeException("ALARM! Podano b³êdny kod PIN dla zamka: " + getName());
    }
}

// Funkcja zwracaj¹ca flagê informuj¹c¹ o stanie zablokowania mechanizmu drzwiowego.
bool SmartLock::isLocked() const {
    return is_locked;
}

// Funkcja zwracaj¹ca zapisan¹ sekwencjê kodu PIN na potrzeby eksportu do pliku binarnego.
std::string SmartLock::getPinCode() const {
    return pin_code;
}

// Funkcja wymuszaj¹ca okreœlony stan rygla podczas odtwarzania danych ze strumienia wejœciowego.
void SmartLock::setLockState(bool state) {
    is_locked = state;
}

// Funkcja generuj¹ca zwiêz³y status blokady przeznaczony dla g³ównego widoku mened¿era urz¹dzeñ.
std::string SmartLock::getDashboardInfo() const {
    return isLocked() ? "[ZAMKNIETY]" : "[OTWARTY]";
}