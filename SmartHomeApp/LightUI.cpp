#include "LightUI.hpp"
#include "SmartHomeException.hpp"

std::string LightUI::handleEvent(sf::Event& event, sf::Vector2f clickPos, SmartLight* light) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
        return "";
    }

    if (!light->isOn()) {
        return "B³¹d: Nie mozna sciemniac wylaczonej zarowki!";
    }

    // Przycisk "- 10%"
    if (sf::FloatRect(300, 250, 80, 60).contains(clickPos)) {
        // Jeœli wartoœæ mia³aby spaœæ poni¿ej 0, blokujemy (zale¿nie od tego jak napisa³eœ core'a)
        int newBright = light->getBrightness() - 10;
        if (newBright < 0) newBright = 0;
        light->setBrightness(newBright);
        return "";
    }

    // Przycisk "+ 10%"
    if (sf::FloatRect(520, 250, 80, 60).contains(clickPos)) {
        int newBright = light->getBrightness() + 10;
        if (newBright > 100) newBright = 100;
        light->setBrightness(newBright);
        return "";
    }

    return "";
}

void LightUI::draw(sf::RenderWindow& window, sf::Font& font, SmartLight* light) {
    sf::Text brightText("Jasnosc Zarowki: " + std::to_string(light->getBrightness()) + "%", font, 28);
    brightText.setPosition(260, 150);
    brightText.setFillColor(sf::Color::Yellow);
    window.draw(brightText);

    // Przycisk Minus
    sf::RectangleShape btnMinus(sf::Vector2f(80, 60));
    btnMinus.setPosition(300, 250);
    btnMinus.setFillColor(sf::Color(80, 80, 100));
    window.draw(btnMinus);

    sf::Text tM("- 10%", font, 20);
    tM.setPosition(315, 265);
    window.draw(tM);

    // Przycisk Plus
    sf::RectangleShape btnPlus(sf::Vector2f(80, 60));
    btnPlus.setPosition(520, 250);
    btnPlus.setFillColor(sf::Color(80, 80, 100));
    window.draw(btnPlus);

    sf::Text tP("+ 10%", font, 20);
    tP.setPosition(535, 265);
    window.draw(tP);
}