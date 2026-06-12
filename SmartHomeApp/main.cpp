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

// G³ówny punkt wejœcia do aplikacji inteligentnego domu.
// Inicjalizuje okno graficzne SFML, podpina bibliotekê interfejsu ImGui, 
// automatycznie wczytuje stan urz¹dzeñ z pliku binarnego i uruchamia pêtlê mened¿era GUI.

int main() {
    std::cout << "[System] Inicjalizacja Smart Home ImGui...\n";

    // utworzenie okna graficznego w rozdzielczoœci xga z zablokowan¹ mo¿liwoœci¹ skalowania bocznego
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Panel Smart Home (ImGui)", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // powi¹zanie kontekstu renderowania imgui z oknem zarz¹dzanym przez bibliotekê sfml
    if (!ImGui::SFML::Init(window)) {
        std::cout << "[BLAD] Nie udalo sie zainicjowac ImGui-SFML!\n";
        return -1;
    }

    // inicjalizacja kluczowych obiektów systemu: kontenera urz¹dzeñ oraz silnika zapisu strumieniowego
    HomeManager myHome;
    BinarySerializer serializer;
    std::string saveFile = "smarthome_save.bin";

    // odtworzenie bazy dodanych urz¹dzeñ z pliku konfiguracyjnego przy starcie programu
    serializer.loadFromFile(myHome, saveFile);

    // przekazanie kontroli nad wyœwietlaniem klatek i obs³ug¹ logiki do g³ównego mened¿era gui
    GuiManager gui(myHome, serializer, saveFile);
    gui.run(window);

    // bezpieczne czyszczenie pamiêci podrêcznej oraz struktur wewnêtrznych imgui przed wyjœciem
    ImGui::SFML::Shutdown();

    return 0;
}