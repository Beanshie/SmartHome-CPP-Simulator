#include "CameraUI.hpp"
#include "imgui.h"

// Implementacja interfejsu graficznego dla modu³u kamery bezpieczeñstwa.
// Odpowiada za rysowanie dedykowanych kontrolek i odczyt stanu rejestracji wideo.

// Funkcja renderuj¹ca stan nagrywania oraz przyciski do sterowania prac¹ kamery.
void CameraUI::render(SecurityCamera* cam) {
    ImGui::Text("Status Kamery: ");
    ImGui::SameLine();

    // sprawdzenie polimorficznego stanu nagrywania
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
        if (ImGui::Button("ROZPOCZNIJ NAGRYWANIE", ImVec2(200, 40))) {
            // w³¹czenie zasilania urz¹dzenia przed startem zapisu
            cam->turnOn();
            cam->startRecording();
        }
    }
}