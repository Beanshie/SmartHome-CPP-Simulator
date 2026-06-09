#include "LightUI.hpp"
#include "imgui.h"

void LightUI::render(SmartLight* light) {
    ImGui::Text("Status Lampy: ");
    ImGui::SameLine();

    if (light->isOn()) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "WLACZONA");

        ImGui::Spacing();

        // --- NOWA FUNKCJONALNOSC: REGULACJA JASNOSCI ---
        ImGui::Text("Jasnosc: %d%%", light->getBrightness());

        if (ImGui::Button("- 10%", ImVec2(95, 30))) {
            light->setBrightness(light->getBrightness() - 10);
        }
        ImGui::SameLine();
        if (ImGui::Button("+ 10%", ImVec2(95, 30))) {
            light->setBrightness(light->getBrightness() + 10);
        }
        // -----------------------------------------------

        ImGui::Spacing();
        if (ImGui::Button("WYLACZ LAMPKE", ImVec2(200, 40))) {
            light->turnOff();
        }
    }
    else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WYLACZONA");

        ImGui::Spacing();
        if (ImGui::Button("WLACZ LAMPKE", ImVec2(200, 40))) {
            light->turnOn();
        }
    }
}