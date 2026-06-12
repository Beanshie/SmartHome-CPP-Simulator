#include "DevicePanelUI.hpp"
#include "imgui.h"

// Definicja g³ównego panelu kontrolnego dla wybranego urz¹dzenia inteligentnego.
// Odpowiada za nawigacjê, diagnostykê sieciow¹ oraz dynamiczne ³adowanie widoków szczegó³owych.

// Konstruktor inicjalizuj¹cy domyœlny stan komunikatów i flag b³êdów.
DevicePanelUI::DevicePanelUI() : current_message(""), is_error(false) {}

// G³ówna funkcja renderuj¹ca interfejs panelu zarz¹dzania i przekierowuj¹ca do widoków podrzêdnych.
int DevicePanelUI::render(SmartDevice* device) {
    int action = 0;

    // powrót do g³ównego menu i czyszczenie buforów stanów
    if (ImGui::Button("< WSTECZ", ImVec2(100, 30))) {
        current_message = "";
        lock_ui.reset();
        therm_ui.reset();
        action = 1;
    }

    // odczyt unikalnego adresu mac za pomoc¹ klasy zaprzyjaŸnionej z urz¹dzeniem
    ImGui::SameLine();
    if (ImGui::Button("DIAGNOZUJ SIEC", ImVec2(150, 30))) {
        NetworkDiagnostics diag;
        current_message = "Adres MAC: " + diag.getDeviceMacAddress(*device);
        is_error = false;
    }

    // zmiana barw na stosie stylów imgui w celu wyró¿nienia przycisku usuwania
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));
    if (ImGui::Button("USUN URZADZENIE", ImVec2(150, 30))) {
        action = 2;
    }
    ImGui::PopStyleColor(3);

    ImGui::Separator();

    // wyœwietlanie nazwy aktualnie obs³ugiwanego obiektu
    ImGui::TextDisabled("Zarzadzanie urzadzeniem:");
    ImGui::TextUnformatted(device->getName().c_str());
    ImGui::Spacing();

    // renderowanie komunikatów diagnostycznych i b³êdów z walidacji
    if (!current_message.empty()) {
        ImVec4 color = is_error ? ImVec4(1.0f, 0.4f, 0.4f, 1.0f) : ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
        ImGui::TextColored(color, "%s", current_message.c_str());
        ImGui::Spacing();
    }

    ImGui::Separator();

    // dynamiczne sprawdzanie typu obiektu (downcasting) i wywo³anie w³aœciwego ui
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