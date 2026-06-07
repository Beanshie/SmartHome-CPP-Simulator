#pragma once
#include <SFML/Graphics.hpp>
#include "SmartLock.hpp"
#include <string>

class LockUI {
private:
    std::string entered_pin; // Przechowuje stan wpisywanego PIN-u tylko dla tego panelu

public:
    LockUI() = default;
    ~LockUI() = default;

    // Rysuje interfejs zamka
    void draw(sf::RenderWindow& window, sf::Font& font, SmartLock* lock);

    // Zwraca treœæ b³êdu (wyj¹tku) lub pusty string, jeœli sukces
    std::string handleEvent(sf::Event& event, sf::Vector2f clickPos, SmartLock* lock);

    // Resetuje PIN (przydatne przy wychodzeniu z panelu)
    void reset();
};