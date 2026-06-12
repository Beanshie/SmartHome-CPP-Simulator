#include "SmartLight.hpp"

// Implementacja zachowañ i specyficznych metod dla inteligentnego Ÿród³a œwiat³a.
// Realizuje zabezpieczenia progowe jasnoœci oraz formatuje polimorficzne komunikaty stanu.

// Konstruktor klasy pochodnej inicjalizuj¹cy klasê bazow¹ oraz domyœlny poziom œwiecenia.
SmartLight::SmartLight(std::string name)
    : SmartDevice(name), brightness(100) {
}

// Funkcja aktywuj¹ca zasilanie ¿arówki za pomoc¹ metody strukturalnej klasy nadrzêdnej.
void SmartLight::turnOn() {
    setStatus(true);
}

// Funkcja odcinaj¹ca zasilanie ¿arówki poprzez zmianê flagi stanu w klasie nadrzêdnej.
void SmartLight::turnOff() {
    setStatus(false);
}

// Funkcja zwracaj¹ca sta³y identyfikator tekstowy podtypu urz¹dzenia dla celów polimorficznych.
std::string SmartLight::getDeviceType() const {
    return "Inteligentna Zarowka";
}

// Funkcja modyfikuj¹ca jasnoœæ z uwzglêdnieniem sztywnych granic bezpieczeñstwa (zakres 10-100%).
void SmartLight::setBrightness(int level) {
    if (level < 10) brightness = 10;
    else if (level > 100) brightness = 100;
    else brightness = level;
}

// Funkcja zwracaj¹ca aktualny poziom jasnoœci zmagazynowany w sk³adowej klasy.
int SmartLight::getBrightness() const {
    return brightness;
}

// Funkcja generuj¹ca dynamiczny ci¹g statusowy z parametrem jasnoœci dla widoku listy GUI.
std::string SmartLight::getDashboardInfo() const {
    return isOn() ? "[ON " + std::to_string(brightness) + "%]" : "[OFF]";
}