#include "ThermostatUI.hpp"
#include "SmartHomeException.hpp"
#include "imgui.h"

// Definicja widoku sterowania termostatem (Thermostat).
// Obs³uguje p³ynn¹ regulacjê docelowej temperatury za pomoc¹ suwaka oraz przechwytuje b³êdy walidacji zakresów.

// Funkcja renderuj¹ca suwak wyboru temperatury i przycisk synchronizacji stanu z warstw¹ logiczn¹.
void ThermostatUI::render(Thermostat* therm) {
    // jednorazowe pobranie bie¿¹cej wartoœci z obiektu w celu synchronizacji suwaka
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

    // poziomy suwak do wyboru wartoœci z zakresu akceptowalnego przez biznesowy rdzeñ aplikacji
    ImGui::SliderFloat("##temp_slider", &temp_buffer, 10.0f, 40.0f, "%.1f C");

    ImGui::Spacing();
    if (ImGui::Button("ZATWIERDZ TEMPERATURE", ImVec2(200, 40))) {
        try {
            // próba zapisu temperatury po zrzutowaniu na typ oczekiwany przez klasê thermostat
            therm->setTemperature(static_cast<double>(temp_buffer));
            error_message = "";
        }
        catch (const SmartHomeException& e) {
            // przechwycenie wyj¹tku w przypadku przekroczenia krytycznych progów bezpieczeñstwa
            error_message = e.what();
        }
    }

    // wypisanie komunikatu b³êdu bezpoœrednio pod przyciskiem akceptacji
    if (!error_message.empty()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "BLAD: %s", error_message.c_str());
    }
}

// Funkcja resetuj¹ca flagi i bufor b³êdów przy opuszczaniu panelu urz¹dzenia.
void ThermostatUI::reset() {
    is_first_render = true;
    error_message = "";
}