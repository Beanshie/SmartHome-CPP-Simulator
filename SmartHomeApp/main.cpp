#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "HomeManager.hpp"
#include "BinarySerializer.hpp"
#include "GuiManager.hpp"

// Nag³ówki startowe
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"

int main() {
    std::cout << "[System] Inicjalizacja Smart Home ImGui...\n";

    // 1. Otworzenie okna SFML ze zablokowanym rozmiarem
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Panel Smart Home (ImGui)", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // 2. Inicjalizacja ImGui podpiêtego do SFML
    if (!ImGui::SFML::Init(window)) {
        std::cout << "[BLAD] Nie udalo sie zainicjowac ImGui-SFML!\n";
        return -1;
    }

    // 3. Konfiguracja domowa
    HomeManager myHome;
    BinarySerializer serializer;
    std::string saveFile = "smarthome_save.bin";

    serializer.loadFromFile(myHome, saveFile);

    // 4. Start systemu graficznego (pêtla jest wewn¹trz klasy!)
    GuiManager gui(myHome, serializer, saveFile);
    gui.run(window);

    // 5. Zamykanie zasobów po zamkniêciu programu
    ImGui::SFML::Shutdown();

    return 0;
}