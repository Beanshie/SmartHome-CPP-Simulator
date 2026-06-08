#include "DevicePanelUI.hpp"
#include "imgui.h"

DevicePanelUI::DevicePanelUI() : current_message(""), is_error(false) {}

int DevicePanelUI::render(SmartDevice* device) {
    int action = 0;

    // --- PASEK NAWIGACJI ---
    if (ImGui::Button("< WSTECZ", ImVec2(100, 30))) {
        current_message = "";
        lock_ui.reset();
        therm_ui.reset();
        action = 1;
    }

    ImGui::SameLine();
    if (ImGui::Button("DIAGNOZUJ SIEC", ImVec2(150, 30))) {
        NetworkDiagnostics diag;
        current_message = "Adres MAC: " + diag.getDeviceMacAddress(*device);
        is_error = false;
    }

    ImGui::SameLine();
    // Kolorowanie przycisku USUÑ na czerwono
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));
    if (ImGui::Button("USUN URZADZENIE", ImVec2(150, 30))) {
        action = 2;
    }
    ImGui::PopStyleColor(3);

    ImGui::Separator();

    // Tytu³ i ewentualne komunikaty sieciowe
    ImGui::TextDisabled("Zarzadzanie urzadzeniem:");
    ImGui::TextUnformatted(device->getName().c_str());
    ImGui::Spacing();

    if (!current_message.empty()) {
        ImVec4 color = is_error ? ImVec4(1.0f, 0.4f, 0.4f, 1.0f) : ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
        ImGui::TextColored(color, "%s", current_message.c_str());
        ImGui::Spacing();
    }

    ImGui::Separator();

    // --- RENDEROWANIE KONKRETNYCH MODU£ÓW ---
    if (auto* lock = dynamic_cast<SmartLock*>(device)) {
        lock_ui.render(lock);
    }
    else if (auto* therm = dynamic_cast<Thermostat*>(device)) {
        therm_ui.render(therm);
    }
    else if (auto* cam = dynamic_cast<SecurityCamera*>(device)) {
        camera_ui.render(cam);
    }
    else if (auto* light = dynamic_cast<SmartLight*>(device)) {
        light_ui.render(light);
    }

    return action;
}