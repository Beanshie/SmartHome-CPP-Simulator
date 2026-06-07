#include "GuiManager.hpp"
#include <iostream>
#include "SmartHomeException.hpp"

GuiManager::GuiManager(HomeManager& h, BinarySerializer& s, std::string filename)
    : hub(h), serializer(s), save_file(filename),
    window(sf::VideoMode(800, 600), "Panel Smart Home (SFML) - Architektura 2.0"),
    current_state(GuiState::Dashboard), // Zaczynamy od menu g³ównego
    selected_device(nullptr) {

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "[BLAD] Nie udalo sie wczytac czcionki Arial!\n";
    }
}

void GuiManager::run() {
    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                serializer.saveToFile(hub, save_file);
                window.close();
            }

            // --- DELEGOWANIE ZDARZEÑ W ZALE¯NOŒCI OD STANU ---
            if (current_state == GuiState::Dashboard) {
                // ... OBS£UGA DASHBOARDU ...
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                    sf::FloatRect btnOnBounds(20, 60, 370, 50);
                    sf::FloatRect btnOffBounds(410, 60, 370, 50);

                    if (btnOnBounds.contains(clickPos)) hub.turnAllOn();
                    if (btnOffBounds.contains(clickPos)) hub.turnAllOff();

                    int yPos = 140;
                    auto& devices = hub.getDevices();
                    for (size_t i = 0; i < devices.size(); ++i) {
                        sf::FloatRect devBounds(20, static_cast<float>(yPos), 760, 60);
                        if (devBounds.contains(clickPos)) {
                            // ZAMIAST ZMIENIAÆ STAN -> WCHODZIMY W SZCZEGÓ£Y
                            selected_device = devices[i].get();
                            current_state = GuiState::DeviceDetails;
                            break; // Przerywamy pêtlê, ¿eby nie klikn¹æ 2 rzeczy naraz
                        }
                        yPos += 75;
                    }
                }
            }
            else if (current_state == GuiState::DeviceDetails && selected_device != nullptr) {
                // ... OBS£UGA PANELU URZ¥DZENIA ...
                // Delegujemy obs³ugê klikniêcia do nowej klasy i wyci¹gamy z niej wybran¹ akcjê
                int action = device_panel.handleEvent(event, window, selected_device);

                if (action == 1) { // WSTECZ
                    current_state = GuiState::Dashboard;
                    selected_device = nullptr;
                }
                else if (action == 2) { // USUNIÊCIE URZ¥DZENIA
                    try {
                        // Zapisujemy nazwê zanim stracimy do niej dostêp przez wyzerowanie wskaŸnika
                        std::string name_to_remove = selected_device->getName();
                        selected_device = nullptr;
                        current_state = GuiState::Dashboard; // Najpierw wracamy do widoku menu
                        hub.removeDevice(name_to_remove);    // Potem bezpiecznie usuwamy element z mened¿era
                    }
                    catch (const SmartHomeException& e) {
                        std::cout << "[BLAD USUNIECIA]: " << e.what() << "\n";
                    }
                }
            }
        }

        // --- RYSOWANIE W ZALE¯NOŒCI OD STANU ---
        if (current_state == GuiState::Dashboard) {

            // --- KOD RYSOWANIA DASHBOARDU (Ten sam co ostatnio) ---
            window.clear(sf::Color(20, 20, 25));

            sf::Text titleText("DASHBOARD SMART HOME", font, 24);
            titleText.setPosition(20, 15);
            titleText.setFillColor(sf::Color(200, 200, 200));
            titleText.setStyle(sf::Text::Bold);
            window.draw(titleText);

            sf::FloatRect btnOnBounds(20, 60, 370, 50);
            bool hoverOn = btnOnBounds.contains(mousePosF);
            sf::RectangleShape btnOn(sf::Vector2f(btnOnBounds.width, btnOnBounds.height));
            btnOn.setPosition(btnOnBounds.left, btnOnBounds.top);
            btnOn.setFillColor(hoverOn ? sf::Color(0, 150, 80) : sf::Color(0, 110, 60));
            btnOn.setOutlineThickness(2);
            btnOn.setOutlineColor(sf::Color(0, 200, 100));
            window.draw(btnOn);

            sf::Text textOn("WLACZ WSZYSTKO", font, 18);
            textOn.setPosition(btnOnBounds.left + 90, btnOnBounds.top + 13);
            window.draw(textOn);

            sf::FloatRect btnOffBounds(410, 60, 370, 50);
            bool hoverOff = btnOffBounds.contains(mousePosF);
            sf::RectangleShape btnOff(sf::Vector2f(btnOffBounds.width, btnOffBounds.height));
            btnOff.setPosition(btnOffBounds.left, btnOffBounds.top);
            btnOff.setFillColor(hoverOff ? sf::Color(180, 50, 50) : sf::Color(130, 30, 30));
            btnOff.setOutlineThickness(2);
            btnOff.setOutlineColor(sf::Color(220, 80, 80));
            window.draw(btnOff);

            sf::Text textOff("WYLACZ WSZYSTKO", font, 18);
            textOff.setPosition(btnOffBounds.left + 90, btnOffBounds.top + 13);
            window.draw(textOff);

            int yPos = 140;
            for (const auto& device : hub.getDevices()) {
                bool isDeviceOn = device->isOn();
                sf::FloatRect devBounds(20, static_cast<float>(yPos), 760, 60);
                bool hoverDev = devBounds.contains(mousePosF);

                sf::RectangleShape devCard(sf::Vector2f(devBounds.width, devBounds.height));
                devCard.setPosition(devBounds.left, devBounds.top);
                sf::Color baseColor = isDeviceOn ? sf::Color(10, 60, 80) : sf::Color(40, 40, 45);
                sf::Color hoverColor = isDeviceOn ? sf::Color(15, 80, 105) : sf::Color(60, 60, 65);

                devCard.setFillColor(hoverDev ? hoverColor : baseColor);
                devCard.setOutlineThickness(2);
                devCard.setOutlineColor(isDeviceOn ? sf::Color(0, 180, 255) : sf::Color(80, 80, 80));
                window.draw(devCard);

                sf::Text statusText(isDeviceOn ? "ON" : "OFF", font, 20);
                statusText.setPosition(devBounds.left + 20, devBounds.top + 18);
                statusText.setFillColor(isDeviceOn ? sf::Color::Green : sf::Color::Red);
                statusText.setStyle(sf::Text::Bold);
                window.draw(statusText);

                sf::Text nameText(device->getName(), font, 20);
                nameText.setPosition(devBounds.left + 80, devBounds.top + 18);
                nameText.setFillColor(sf::Color::White);
                window.draw(nameText);

                sf::Text typeText(device->getDeviceType(), font, 16);
                typeText.setPosition(devBounds.left + 550, devBounds.top + 20);
                typeText.setFillColor(sf::Color(150, 150, 150));
                window.draw(typeText);

                yPos += 75;
            }
        }
        else if (current_state == GuiState::DeviceDetails && selected_device != nullptr) {
            // --- DELEGOWANIE RYSOWANIA DO NOWEJ KLASY ---
            device_panel.drawPanel(window, selected_device, font);
        }

        window.display();
    }
}