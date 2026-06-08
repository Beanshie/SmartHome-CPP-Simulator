#pragma once
#include "SmartDevice.hpp"
#include "LockUI.hpp"
#include "ThermostatUI.hpp"
#include "CameraUI.hpp"
#include "LightUI.hpp"
#include "NetworkDiagnostics.hpp"
#include <string>

class DevicePanelUI {
private:
    std::string current_message;
    bool is_error;

    LockUI lock_ui;
    ThermostatUI therm_ui;
    CameraUI camera_ui;
    LightUI light_ui;

public:
    DevicePanelUI();
    ~DevicePanelUI() = default;

    // Zwraca 0 (nic), 1 (wstecz), 2 (usun)
    int render(SmartDevice* device);
};