#pragma once
#include <SFML/Graphics.hpp>
#include "SmartLight.hpp"
#include <string>

class LightUI {
public:
    LightUI() = default;
    ~LightUI() = default;

    void draw(sf::RenderWindow& window, sf::Font& font, SmartLight* light);
    std::string handleEvent(sf::Event& event, sf::Vector2f clickPos, SmartLight* light);
};