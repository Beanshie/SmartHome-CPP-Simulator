#include "LockUI.hpp"
#include "SmartHomeException.hpp"

std::string LockUI::handleEvent(sf::Event& event, sf::Vector2f clickPos, SmartLock* lock) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
        return "";
    }

    // Klawiatura 1-9
    for (int i = 0; i < 9; i++) {
        float x = 300 + (i % 3) * 70;
        float y = 150 + (i / 3) * 70;
        if (sf::FloatRect(x, y, 60, 60).contains(clickPos) && entered_pin.length() < 8) {
            entered_pin += std::to_string(i + 1);
            return "";
        }
    }

    // Przycisk "0"
    if (sf::FloatRect(370, 360, 60, 60).contains(clickPos) && entered_pin.length() < 8) {
        entered_pin += "0";
        return "";
    }

    // Przycisk "C" (Clear)
    if (sf::FloatRect(300, 360, 60, 60).contains(clickPos)) {
        entered_pin = "";
        return "";
    }

    // Przycisk "POTWIERD PIN" (Tutaj ³apiemy Twój wyj¹tek z DLL!)
    if (sf::FloatRect(300, 430, 200, 50).contains(clickPos)) {
        try {
            lock->unlock(entered_pin);
            entered_pin = ""; // Reset po udanym otwarciu
            return "";
        }
        catch (const SmartHomeException& e) {
            entered_pin = ""; // Reset po b³êdnym PIN-ie
            return e.what();  // Zwracamy b³¹d z Core'a do wyœwietlenia
        }
    }

    // Przycisk "ZABLOKUJ"
    if (sf::FloatRect(520, 430, 150, 50).contains(clickPos)) {
        lock->lock();
        return "";
    }

    return "";
}

void LockUI::draw(sf::RenderWindow& window, sf::Font& font, SmartLock* lock) {
    // Status
    sf::Text lockState(lock->isLocked() ? "ZABLOKOWANY" : "OTWARTY", font, 22);
    lockState.setPosition(50, 190);
    lockState.setFillColor(lock->isLocked() ? sf::Color::Red : sf::Color::Green);
    window.draw(lockState);

    // Wyœwietlacz PIN
    sf::RectangleShape pinBox(sf::Vector2f(200, 40));
    pinBox.setPosition(300, 90);
    pinBox.setFillColor(sf::Color::Black);
    pinBox.setOutlineThickness(2);
    pinBox.setOutlineColor(sf::Color::Cyan);
    window.draw(pinBox);

    std::string hidden_pin(entered_pin.length(), '*');
    sf::Text pinText(hidden_pin, font, 24);
    pinText.setPosition(310, 95);
    pinText.setFillColor(sf::Color::White);
    window.draw(pinText);

    // Rysowanie klawiatury
    for (int i = 0; i < 9; i++) {
        float x = 300 + (i % 3) * 70;
        float y = 150 + (i / 3) * 70;

        sf::RectangleShape btn(sf::Vector2f(60, 60));
        btn.setPosition(x, y);
        btn.setFillColor(sf::Color(60, 60, 70));
        window.draw(btn);

        sf::Text num(std::to_string(i + 1), font, 24);
        num.setPosition(x + 22, y + 15);
        window.draw(num);
    }

    sf::RectangleShape btnC(sf::Vector2f(60, 60)); btnC.setPosition(300, 360); btnC.setFillColor(sf::Color(100, 40, 40)); window.draw(btnC);
    sf::Text tC("C", font, 24); tC.setPosition(320, 375); window.draw(tC);

    sf::RectangleShape btn0(sf::Vector2f(60, 60)); btn0.setPosition(370, 360); btn0.setFillColor(sf::Color(60, 60, 70)); window.draw(btn0);
    sf::Text t0("0", font, 24); t0.setPosition(392, 375); window.draw(t0);

    sf::RectangleShape btnUnlock(sf::Vector2f(200, 50)); btnUnlock.setPosition(300, 430); btnUnlock.setFillColor(sf::Color(0, 120, 60)); window.draw(btnUnlock);
    sf::Text tU("POTWIERDZ PIN", font, 18); tU.setPosition(325, 445); window.draw(tU);

    sf::RectangleShape btnLock(sf::Vector2f(150, 50)); btnLock.setPosition(520, 430); btnLock.setFillColor(sf::Color(120, 0, 0)); window.draw(btnLock);
    sf::Text tL("ZABLOKUJ", font, 18); tL.setPosition(545, 445); window.draw(tL);
}

void LockUI::reset() {
    entered_pin = "";
}