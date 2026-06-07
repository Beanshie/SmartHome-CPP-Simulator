#include "DevicePanelUI.hpp"
#include "SmartHomeException.hpp"
#include <iostream>

int DevicePanelUI::handleEvent(sf::Event& event, sf::RenderWindow& window, SmartDevice* device) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        // [ WSTECZ ]
        if (sf::FloatRect(20, 20, 150, 40).contains(clickPos)) {
            current_error_message = "";
            entered_pin = ""; // Czyœcimy PIN przy wyjœciu
            return 1;
        }

        // [ USUÑ URZ¥DZENIE ] - Nowa funkcjonalnoœæ!
        if (sf::FloatRect(590, 20, 190, 40).contains(clickPos)) {
            return 2;
        }

        // --- RTTI: ROZPOZNAWANIE TYPU URZ¥DZENIA ---
        if (auto* lock = dynamic_cast<SmartLock*>(device)) {
            handleLockEvent(event, lock, clickPos);
        }
        // W przysz³oœci mo¿esz tu dodaæ: else if (auto* therm = dynamic_cast<Thermostat*>(device)) { ... }
    }
    return 0;
}

void DevicePanelUI::handleLockEvent(sf::Event& event, SmartLock* lock, sf::Vector2f clickPos) {
    // Sprawdzanie klikniêæ w klawiaturê numeryczn¹ (0-9)
    for (int i = 0; i < 9; i++) {
        float x = 300 + (i % 3) * 70;
        float y = 150 + (i / 3) * 70;
        if (sf::FloatRect(x, y, 60, 60).contains(clickPos) && entered_pin.length() < 8) {
            entered_pin += std::to_string(i + 1);
            current_error_message = ""; // Czyœcimy b³¹d po nowym klikniêciu
        }
    }
    // Przycisk "0"
    if (sf::FloatRect(370, 360, 60, 60).contains(clickPos) && entered_pin.length() < 8) {
        entered_pin += "0";
        current_error_message = "";
    }

    // Przycisk "C" (Clear)
    if (sf::FloatRect(300, 360, 60, 60).contains(clickPos)) entered_pin = "";

    // Przycisk "OTWÓRZ" (Wysy³amy PIN do urz¹dzenia!)
    if (sf::FloatRect(300, 430, 200, 50).contains(clickPos)) {
        try {
            lock->unlock(entered_pin); // TU U¯YWAMY METODY Z CORE
            entered_pin = "";
            current_error_message = "";
        }
        catch (const SmartHomeException& e) {
            // £APIEMY TWÓJ WYJ¥TEK!
            current_error_message = e.what();
            entered_pin = "";
        }
    }

    // Przycisk "ZABLOKUJ"
    if (sf::FloatRect(520, 430, 150, 50).contains(clickPos)) {
        lock->lock();
        current_error_message = "";
    }
}

void DevicePanelUI::drawPanel(sf::RenderWindow& window, SmartDevice* device, sf::Font& font) {
    window.clear(sf::Color(25, 30, 40));

    // Nag³ówek i przycisk WSTECZ
    sf::RectangleShape backBtn(sf::Vector2f(150, 40));
    backBtn.setPosition(20, 20);
    backBtn.setFillColor(sf::Color(80, 80, 90));
    window.draw(backBtn);
    sf::Text backText("< WSTECZ", font, 18);
    backText.setPosition(45, 28);
    window.draw(backText);

    // Przycisk USUÑ
    sf::RectangleShape delBtn(sf::Vector2f(190, 40));
    delBtn.setPosition(590, 20);
    delBtn.setFillColor(sf::Color(150, 40, 40));
    window.draw(delBtn);
    sf::Text delText("USUN URZADZENIE", font, 16);
    delText.setPosition(605, 30);
    window.draw(delText);

    // Tytu³
    sf::Text titleText("Panel: " + device->getName(), font, 24);
    titleText.setPosition(190, 25);
    titleText.setFillColor(sf::Color::White);
    window.draw(titleText);

    sf::RectangleShape line(sf::Vector2f(760, 2));
    line.setPosition(20, 80);
    line.setFillColor(sf::Color(100, 100, 100));
    window.draw(line);

    // Wyœwietlanie ewentualnego wyj¹tku
    if (!current_error_message.empty()) {
        sf::Text errText(current_error_message, font, 18);
        errText.setPosition(20, 90);
        errText.setFillColor(sf::Color::Red);
        window.draw(errText);
    }

    // --- RYSOWANIE SPECYFICZNE DLA TYPU ---
    if (auto* lock = dynamic_cast<SmartLock*>(device)) {
        drawLockPanel(lock, window, font);
    }
    else {
        sf::Text info("Brak zaawansowanego interfejsu dla tego urzadzenia.", font, 20);
        info.setPosition(20, 150);
        window.draw(info);
    }
}

void DevicePanelUI::drawLockPanel(SmartLock* lock, sf::RenderWindow& window, sf::Font& font) {
    // Status Zamka
    sf::Text statusText("Status Zamka: ", font, 22);
    statusText.setPosition(50, 150);
    window.draw(statusText);

    sf::Text lockState(lock->isLocked() ? "ZABLOKOWANY" : "OTWARTY", font, 22);
    lockState.setPosition(50, 190);
    lockState.setFillColor(lock->isLocked() ? sf::Color::Red : sf::Color::Green);
    lockState.setStyle(sf::Text::Bold);
    window.draw(lockState);

    // Ekranik na PIN
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

    // Klawiatura 1-9
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

    // Przycisk C i 0
    sf::RectangleShape btnC(sf::Vector2f(60, 60));
    btnC.setPosition(300, 360);
    btnC.setFillColor(sf::Color(100, 40, 40));
    window.draw(btnC);
    sf::Text tC("C", font, 24);
    tC.setPosition(320, 375);
    window.draw(tC);

    sf::RectangleShape btn0(sf::Vector2f(60, 60));
    btn0.setPosition(370, 360);
    btn0.setFillColor(sf::Color(60, 60, 70));
    window.draw(btn0);
    sf::Text t0("0", font, 24);
    t0.setPosition(392, 375);
    window.draw(t0);

    // Akcje Zamka
    sf::RectangleShape btnUnlock(sf::Vector2f(200, 50));
    btnUnlock.setPosition(300, 430);
    btnUnlock.setFillColor(sf::Color(0, 120, 60));
    window.draw(btnUnlock);
    sf::Text tU("POTWIERDZ PIN", font, 18);
    tU.setPosition(325, 445);
    window.draw(tU);

    sf::RectangleShape btnLock(sf::Vector2f(150, 50));
    btnLock.setPosition(520, 430);
    btnLock.setFillColor(sf::Color(120, 0, 0));
    window.draw(btnLock);
    sf::Text tL("ZABLOKUJ", font, 18);
    tL.setPosition(545, 445);
    window.draw(tL);
}