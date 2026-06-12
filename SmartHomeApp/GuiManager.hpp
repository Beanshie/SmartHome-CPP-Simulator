#pragma once
#include "HomeManager.hpp"
#include "BinarySerializer.hpp"
#include "DevicePanelUI.hpp"
#include <SFML/Graphics.hpp>
#include <string>

// stany okna, zeby wiedziec co aktualnie wyswietlac
enum class GuiState {
    Dashboard,
    DeviceDetails
};

enum class AddDeviceType {
    None, Light, Thermostat, Camera, Lock
};

// glowny zarzadca calego gui. spina sfml, imgui i nasza logike w jedna calosc.
class GuiManager {
private:
    // referencje do bebechow systemu, gui samo w sobie nie "posiada" tych obiektow
    HomeManager& hub;
    BinarySerializer& serializer;
    std::string save_file;

    GuiState current_state;
    SmartDevice* selected_device;
    DevicePanelUI device_panel;

    // tablice znakow dla imgui, musi miec cos na sztywno w pamieci zeby dzialalo wpisywanie
    char name_buffer[64];
    char pin_buffer[16];
    AddDeviceType pending_device_type;

public:
    GuiManager(HomeManager& h, BinarySerializer& s, std::string filename);
    ~GuiManager() = default;

    // glowna petla rysujaca klatki
    void run(sf::RenderWindow& window);
};