#include "CameraUI.hpp"

std::string CameraUI::handleEvent(sf::Event& event, sf::Vector2f clickPos, SecurityCamera* cam) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
        return "";
    }

    if (!cam->isOn()) {
        return "B³¹d: Kamera jest wylaczona z pradu!";
    }

    // Przycisk "START REC"
    if (sf::FloatRect(250, 250, 150, 50).contains(clickPos)) {
        cam->startRecording();
        return "";
    }

    // Przycisk "STOP REC"
    if (sf::FloatRect(450, 250, 150, 50).contains(clickPos)) {
        cam->stopRecording();
        return "";
    }

    return "";
}

void CameraUI::draw(sf::RenderWindow& window, sf::Font& font, SecurityCamera* cam) {
    // Dynamiczny status nagrywania (zmienia kolor z zielonego na czerwony)
    sf::Text statText(cam->isRecording() ? "STATUS: NAGRYWANIE" : "STATUS: CZUWANIE", font, 28);
    statText.setPosition(250, 150);
    statText.setFillColor(cam->isRecording() ? sf::Color::Red : sf::Color::Green);
    statText.setStyle(sf::Text::Bold);
    window.draw(statText);

    // Przycisk Rozpoczêcia Nagrywania
    sf::RectangleShape btnRec(sf::Vector2f(150, 50));
    btnRec.setPosition(250, 250);
    btnRec.setFillColor(sf::Color(150, 0, 0));
    window.draw(btnRec);

    sf::Text tRec("START REC", font, 18);
    tRec.setPosition(275, 265);
    window.draw(tRec);

    // Przycisk Zatrzymania Nagrywania
    sf::RectangleShape btnStop(sf::Vector2f(150, 50));
    btnStop.setPosition(450, 250);
    btnStop.setFillColor(sf::Color(100, 100, 100));
    window.draw(btnStop);

    sf::Text tStop("STOP REC", font, 18);
    tStop.setPosition(480, 265);
    window.draw(tStop);
}