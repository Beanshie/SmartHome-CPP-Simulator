#pragma once
#include "SmartDevice.hpp"
#include "LockUI.hpp"
#include "ThermostatUI.hpp"
#include "CameraUI.hpp"
#include "LightUI.hpp"
#include "NetworkDiagnostics.hpp"
#include <string>

// glowny panel dla wybranego urzadzenia. dziala jak router,
// ktory decyduje ktory konkretny interfejs (np. od zamka czy swiatla) odpalic.
class DevicePanelUI {
private:
    // bufory na komunikaty dla uzytkownika (np. b³êdy z wyj¹tków)
    std::string current_message;
    bool is_error;

    // instancje pod-widokow, trzymane tutaj zeby nie tracily swojego stanu (np. wpisanego pinu)
    LockUI lock_ui;
    ThermostatUI therm_ui;
    CameraUI camera_ui;
    LightUI light_ui;

public:
    DevicePanelUI();
    ~DevicePanelUI() = default;

    // zwraca inta zeby glowny manager wiedzial co zrobic
    // 0 - zostan, 1 - wroc do menu, 2 - wywal urzadzenie
    int render(SmartDevice* device);
};