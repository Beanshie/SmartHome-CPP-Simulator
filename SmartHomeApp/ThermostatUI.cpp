#include "ThermostatUI.hpp"
#include "SmartHomeException.hpp"
#include "imgui.h"

void ThermostatUI::render(Thermostat* therm) {
    // Przy pierwszym wejœciu w szczegó³y, ustawiamy suwak na aktualn¹ temperaturê
    if (is_first_render) {
        temp_buffer = static_cast<float>(therm->getTemperature());
        is_first_render = false;
    }

    ImGui::Text("Aktualna temperatura: ");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%.1f C", therm->getTemperature());

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Ustaw nowa temperature:");

    // Gotowy suwak w 1 linijce! Parametry: Etykieta, wskaŸnik do wartoœci, Min, Max, Format
    ImGui::SliderFloat("##temp_slider", &temp_buffer, 10.0f, 40.0f, "%.1f C");

    ImGui::Spacing();
    if (ImGui::Button("ZATWIERDZ TEMPERATURE", ImVec2(200, 40))) {
        try {
            therm->setTemperature(static_cast<double>(temp_buffer));
            error_message = "";
        }
        catch (const SmartHomeException& e) {
            error_message = e.what();
        }
    }

    if (!error_message.empty()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "BLAD: %s", error_message.c_str());
    }
}

void ThermostatUI::reset() {
    is_first_render = true;
    error_message = "";
}