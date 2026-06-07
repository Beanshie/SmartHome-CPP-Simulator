#pragma once
#include <SFML/Graphics.hpp>
#include "SmartDevice.hpp"
#include "SmartLock.hpp" // Musimy do³¹czyæ konkretne urz¹dzenia
#include <string>

class DevicePanelUI {
private:
    std::string current_error_message;
    std::string entered_pin; // Przechowuje PIN wpisywany na klawiaturze

    // Prywatne metody do obs³ugi konkretnych urz¹dzeñ (RTTI)
    void drawLockPanel(SmartLock* lock, sf::RenderWindow& window, sf::Font& font);
    void handleLockEvent(sf::Event& event, SmartLock* lock, sf::Vector2f clickPos);

public:
    DevicePanelUI() = default;
    ~DevicePanelUI() = default;

    // Zmieniamy typ zwracany na int, ¿eby Mened¿er wiedzia³, co zrobiliœmy:
    // 0 = Nic, 1 = Wstecz, 2 = Usuñ Urz¹dzenie
    int handleEvent(sf::Event& event, sf::RenderWindow& window, SmartDevice* device);

    void drawPanel(sf::RenderWindow& window, SmartDevice* device, sf::Font& font);
};