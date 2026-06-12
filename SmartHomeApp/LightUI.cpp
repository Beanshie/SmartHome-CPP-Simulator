#include "LightUI.hpp"
#include "imgui.h"

// Definicja widoku sterowania inteligentnym Ÿród³em œwiat³a.
// Umo¿liwia prze³¹czanie stanu zasilania oraz stopniow¹ regulacjê jasnoœci lampy w krokach co 10%.

// Funkcja renderuj¹ca panel sterowania oœwietleniem oraz obs³uguj¹ca klikniêcia przycisków.
void LightUI::render(SmartLight* light) {
    ImGui::Text("Status Lampy: ");
    ImGui::SameLine();

    // rysowanie odpowiedniego zestawu kontrolek na podstawie stanu zasilania
    if (light->isOn()) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "WLACZONA");

        ImGui::Spacing();

        // formatowanie napisu z aktualnym poziomem jasnoœci lampy
        ImGui::Text("Jasnosc: %d%%", light->getBrightness());

        // przyciski do skokowej modyfikacji natê¿enia œwiat³a
        if (ImGui::Button("- 10%", ImVec2(95, 30))) {
            light->setBrightness(light->getBrightness() - 10);
        }
        ImGui::SameLine();
        if (ImGui::Button("+ 10%", ImVec2(95, 30))) {
            light->setBrightness(light->getBrightness() + 10);
        }

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