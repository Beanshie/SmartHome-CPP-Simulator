#include "ThermostatUI.hpp"
#include "SmartHomeException.hpp"
#include <sstream>
#include <iomanip>

std::string ThermostatUI::handleEvent(sf::Event& event, sf::Vector2f clickPos, Thermostat* therm) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
        return "";
    }

    if (!therm->isOn()) {
        return "B³¹d: Termostat musi byc wlaczony, aby zmienic temperature!";
    }

    try {
        if (sf::FloatRect(300, 250, 80, 80).contains(clickPos)) { // Przycisk MINUS
            therm->setTemperature(therm->getTemperature() - 1.0);
            return "";
        }
        if (sf::FloatRect(520, 250, 80, 80).contains(clickPos)) { // Przycisk PLUS
            therm->setTemperature(therm->getTemperature() + 1.0);
            return "";
        }
    }
    catch (const SmartHomeException& e) {
        return e.what(); // Z³apie próbê wyjœcia poza 10-40 stopni
    }

    return "";
}

void ThermostatUI::draw(sf::RenderWindow& window, sf::Font& font, Thermostat* therm) {
    sf::Text tempTitle("Obecna Temperatura:", font, 24);
    tempTitle.setPosition(280, 150);
    window.draw(tempTitle);

    // Formatowanie temperatury do 1 miejsca po przecinku
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << therm->getTemperature();

    sf::Text tempDisplay(stream.str() + " *C", font, 48);
    tempDisplay.setPosition(330, 180);
    tempDisplay.setFillColor(sf::Color(255, 150, 0));
    window.draw(tempDisplay);

    sf::RectangleShape btnMinus(sf::Vector2f(80, 80));
    btnMinus.setPosition(300, 250);
    btnMinus.setFillColor(sf::Color(80, 80, 100));
    window.draw(btnMinus);

    sf::Text tM("-", font, 48);
    tM.setPosition(330, 255);
    window.draw(tM);

    sf::RectangleShape btnPlus(sf::Vector2f(80, 80));
    btnPlus.setPosition(520, 250);
    btnPlus.setFillColor(sf::Color(80, 80, 100));
    window.draw(btnPlus);

    sf::Text tP("+", font, 48);
    tP.setPosition(545, 255);
    window.draw(tP);
}