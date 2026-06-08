#pragma once
#include "HomeManager.hpp"
#include "BinarySerializer.hpp"
#include "DevicePanelUI.hpp"
#include <SFML/Graphics.hpp>
#include <string>

enum class GuiState {
    Dashboard,
    DeviceDetails
};

enum class AddDeviceType {
    None, Light, Thermostat, Camera, Lock
};

class GuiManager {
private:
    HomeManager& hub;
    BinarySerializer& serializer;
    std::string save_file;

    GuiState current_state;
    SmartDevice* selected_device;
    DevicePanelUI device_panel;

    // Bufory do ImGui
    char name_buffer[64];
    char pin_buffer[16];
    AddDeviceType pending_device_type;

public:
    GuiManager(HomeManager& h, BinarySerializer& s, std::string filename);
    ~GuiManager() = default;

    void run(sf::RenderWindow& window);
};