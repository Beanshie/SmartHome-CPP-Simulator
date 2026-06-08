#include "LightUI.hpp"
#include "imgui.h"

void LightUI::render(SmartLight* light) {
    ImGui::Text("Status Lampy: ");
    ImGui::SameLine(); // Sprawia, ¿e kolejny element bêdzie w tej samej linijce, a nie pod spodem

    if (light->isOn()) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "WLACZONA"); // Zielony tekst

        ImGui::Spacing(); // Pusty odstêp dla czytelnoœci
        if (ImGui::Button("WYLACZ LAMPKE", ImVec2(200, 40))) {
            light->turnOff();
        }
    }
    else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WYLACZONA"); // Czerwony tekst

        ImGui::Spacing();
        if (ImGui::Button("WLACZ LAMPKE", ImVec2(200, 40))) {
            light->turnOn();
        }
    }
}