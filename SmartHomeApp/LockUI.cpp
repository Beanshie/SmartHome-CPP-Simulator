#include "LockUI.hpp"
#include "SmartHomeException.hpp"
#include "imgui.h"

// Definicja widoku dla elektronicznego zamka drzwi (SmartLock).
// Obs³uguje bezpieczne wprowadzanie kodu PIN, autoryzacjê oraz przechwytywanie wyj¹tków walidacji.

// Funkcja rysuj¹ca pole tekstowe typu password oraz przyciski do zmiany stanu rygla.
void LockUI::render(SmartLock* lock) {
    ImGui::Text("Status Zamka: ");
    ImGui::SameLine();

    if (lock->isLocked()) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "ZABLOKOWANY");

        ImGui::Spacing();
        ImGui::Text("Wprowadz PIN z klawiatury:");

        // maskowanie wpisywanych znaków na ekranie przy u¿yciu flagi imgui
        ImGui::InputText("##pin_input", pin_buffer, sizeof(pin_buffer), ImGuiInputTextFlags_Password);

        ImGui::Spacing();
        if (ImGui::Button("ODBLOKUJ", ImVec2(200, 40))) {
            try {
                // próba autoryzacji wpisanym buforem tekstowym
                lock->unlock(std::string(pin_buffer));
                error_message = "";
                pin_buffer[0] = '\0';
            }
            catch (const SmartHomeException& e) {
                // przechwycenie b³êdu z warstwy logiki w przypadku z³ego kodu pin
                error_message = e.what();
            }
        }
    }
    else {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "OTWARTY");

        ImGui::Spacing();
        if (ImGui::Button("ZABLOKUJ", ImVec2(200, 40))) {
            lock->lock();
            error_message = "";
        }
    }

    // wyœwietlanie komunikatów o b³êdach autoryzacji bezpoœrednio w panelu
    if (!error_message.empty()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "BLAD: %s", error_message.c_str());
    }
}

// Funkcja czyszcz¹ca bufory pamiêci podrêcznej okna przed ponownym otwarciem.
void LockUI::reset() {
    pin_buffer[0] = '\0';
    error_message = "";
}