#pragma once
#include <SFML/Graphics.hpp>
#include "Thermostat.hpp"
#include <string>

class ThermostatUI {
public:
    ThermostatUI() = default;
    ~ThermostatUI() = default;

    void draw(sf::RenderWindow& window, sf::Font& font, Thermostat* therm);
    std::string handleEvent(sf::Event& event, sf::Vector2f clickPos, Thermostat* therm);
};