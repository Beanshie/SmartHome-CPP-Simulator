#include "CameraUI.hpp"
#include "imgui.h"

void CameraUI::render(SecurityCamera* cam) {
    ImGui::Text("Status Kamery: ");
    ImGui::SameLine();

    if (cam->isRecording()) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[ REC ] NAGRYWANIE TRWA");
        ImGui::Spacing();
        if (ImGui::Button("ZATRZYMAJ NAGRYWANIE", ImVec2(200, 40))) {
            cam->stopRecording();
        }
    }
    else {
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "W GOTOWOSCI");
        ImGui::Spacing();
        // --- TU JEST NAPRAWA ---
        if (ImGui::Button("ROZPOCZNIJ NAGRYWANIE", ImVec2(200, 40))) {
            cam->turnOn();         // Najpierw w³¹cz zasilanie (ustawia isOn na true)
            cam->startRecording(); // Teraz to zadzia³a, bo isOn() jest true
        }
    }
}