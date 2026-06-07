#pragma once
#include <SFML/Graphics.hpp>
#include "SecurityCamera.hpp"
#include <string>

class CameraUI {
public:
    CameraUI() = default;
    ~CameraUI() = default;

    void draw(sf::RenderWindow& window, sf::Font& font, SecurityCamera* cam);
    std::string handleEvent(sf::Event& event, sf::Vector2f clickPos, SecurityCamera* cam);
};