#pragma once
#include "HomeManager.hpp"
#include "BinarySerializer.hpp"
#include "DevicePanelUI.hpp" // Podpinamy nasz nowy UI
#include <SFML/Graphics.hpp>
#include <string>

// Nasza maszyna stanów!
enum class GuiState {
    Dashboard,
    DeviceDetails
};

class GuiManager {
private:
    HomeManager& hub;
    BinarySerializer& serializer;
    std::string save_file;

    sf::RenderWindow window;
    sf::Font font;

    // Zmienne do zarz¹dzania stanami ekranu
    GuiState current_state;
    SmartDevice* selected_device;
    DevicePanelUI device_panel;

public:
    GuiManager(HomeManager& h, BinarySerializer& s, std::string filename);
    ~GuiManager() = default;

    void run();
};