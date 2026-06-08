#include "LockUI.hpp"
#include "SmartHomeException.hpp"
#include "imgui.h"

void LockUI::render(SmartLock* lock) {
    ImGui::Text("Status Zamka: ");
    ImGui::SameLine();

    if (lock->isLocked()) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "ZABLOKOWANY");

        ImGui::Spacing();
        ImGui::Text("Wprowadz PIN z klawiatury:");

        // Magia ImGui: gotowe pole na has³o, ukrywaj¹ce znaki
        ImGui::InputText("##pin_input", pin_buffer, sizeof(pin_buffer), ImGuiInputTextFlags_Password);

        ImGui::Spacing();
        if (ImGui::Button("ODBLOKUJ", ImVec2(200, 40))) {
            try {
                lock->unlock(std::string(pin_buffer));
                error_message = "";        // Czyœcimy b³¹d po sukcesie
                pin_buffer[0] = '\0';      // Czyœcimy pole PIN
            }
            catch (const SmartHomeException& e) {
                error_message = e.what();  // £apiemy wyj¹tek z Core'a
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

    // Wyœwietlanie b³êdu pod przyciskami (np. Z³y PIN)
    if (!error_message.empty()) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.0f, 1.0f), "BLAD: %s", error_message.c_str());
    }
}

void LockUI::reset() {
    pin_buffer[0] = '\0';
    error_message = "";
}