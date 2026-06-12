#include "GuiManager.hpp"
#include "SmartHomeException.hpp"
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>

// Definicja g³ównego mened¿era GUI ³¹cz¹cego bibliotekê graficzn¹ SFML z kontrolkami ImGui.
// Zarz¹dza pêtl¹ zdarzeñ okna, stanami aplikacji oraz dynamicznym dodawaniem i usuwaniem obiektów.

// Konstruktor mapuj¹cy referencje do logiki biznesowej i inicjalizuj¹cy bufory tekstowe dla formularzy.
GuiManager::GuiManager(HomeManager& h, BinarySerializer& s, std::string filename)
    : hub(h), serializer(s), save_file(filename),
    current_state(GuiState::Dashboard),
    selected_device(nullptr),
    pending_device_type(AddDeviceType::None) {
    name_buffer[0] = '\0';
    pin_buffer[0] = '\0';
}

// G³ówna pêtla programu przetwarzaj¹ca zdarzenia systemowe, logikê renderowania i odœwie¿anie okna.
void GuiManager::run(sf::RenderWindow& window) {
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        // pêtla przechwytuj¹ca zdarzenia od systemu operacyjnego i myszy
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                // automatyczny zapis konfiguracji przy próbie zamkniêcia programu
                serializer.saveToFile(hub, save_file);
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // rozci¹gniêcie g³ównego okna graficznego na ca³¹ dostêpn¹ przestrzeñ
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)window.getSize().x, (float)window.getSize().y));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Main UI", nullptr, window_flags);

        // renderowanie g³ównego ekranu z list¹ wszystkich posiadanych urz¹dzeñ
        if (current_state == GuiState::Dashboard) {
            ImGui::Text("DASHBOARD SMART HOME");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("Twoje urzadzenia (kliknij, by zarzadzac):");
            ImGui::BeginChild("DeviceList", ImVec2(0, 500), true);

            // iteracja po urz¹dzeniach przy u¿yciu polimorfizmu i metod wirtualnych
            for (const auto& device : hub.getDevices()) {
                std::string info = device->getDashboardInfo();

                if (auto* lock = dynamic_cast<SmartLock*>(device.get())) {
                    // kolor czerwony dla zablokowanego zamka, zielony dla otwartego
                    ImGui::PushStyleColor(ImGuiCol_Text, lock->isLocked() ? ImVec4(1.0f, 0.2f, 0.2f, 1.0f) : ImVec4(0.2f, 1.0f, 0.2f, 1.0f));
                }
                else {
                    // dynamiczne dobieranie barwy tekstu na bazie statusu tekstowego z biblioteki core
                    bool is_active = (info != "[OFF]" && info != "[GOTOWA]");
                    ImGui::PushStyleColor(ImGuiCol_Text, is_active ? ImVec4(0.2f, 1.0f, 0.2f, 1.0f) : ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
                }

                ImGui::Text(info.c_str());
                ImGui::PopStyleColor();
                ImGui::SameLine();

                // sprawdzenie wyboru danego elementu z listy
                if (ImGui::Selectable(device->getName().c_str())) {
                    selected_device = device.get();
                    current_state = GuiState::DeviceDetails;
                }
            }
            ImGui::EndChild();
            ImGui::Separator();

            ImGui::SetCursorPosY(670);
            ImGui::Text("Dodaj nowe urzadzenie:");
            if (ImGui::Button("+ Lampa", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Light; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Termostat", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Thermostat; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Kamera", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Camera; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Zamek", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Lock; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }

            // otwieranie okna wyskakuj¹cego dla formularza kreacji nowego sprzêtu
            if (ImGui::BeginPopupModal("Konfiguracja Urzadzenia", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Wprowadz wlasna nazwe urzadzenia:");
                ImGui::InputText("##name", name_buffer, sizeof(name_buffer));
                if (pending_device_type == AddDeviceType::Lock) {
                    ImGui::Spacing();
                    ImGui::Text("Ustaw bezpieczny PIN:");
                    ImGui::InputText("##pin", pin_buffer, sizeof(pin_buffer), ImGuiInputTextFlags_Password);
                }
                ImGui::Spacing();
                ImGui::Separator();

                // zatwierdzenie formularza i przekazanie w³asnego unique_ptr do managera
                if (ImGui::Button("ZATWIERDZ I DODAJ", ImVec2(150, 0))) {
                    std::string final_name = (name_buffer[0] == '\0') ? "Nieznane" : std::string(name_buffer);
                    if (pending_device_type == AddDeviceType::Light) hub.addDevice(std::make_unique<SmartLight>(final_name));
                    else if (pending_device_type == AddDeviceType::Thermostat) hub.addDevice(std::make_unique<Thermostat>(final_name));
                    else if (pending_device_type == AddDeviceType::Camera) hub.addDevice(std::make_unique<SecurityCamera>(final_name));
                    else if (pending_device_type == AddDeviceType::Lock) {
                        std::string final_pin = (pin_buffer[0] == '\0') ? "0000" : std::string(pin_buffer);
                        hub.addDevice(std::make_unique<SmartLock>(final_name, final_pin));
                    }
                    name_buffer[0] = '\0'; pin_buffer[0] = '\0';
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("ANULUJ", ImVec2(100, 0))) {
                    name_buffer[0] = '\0'; pin_buffer[0] = '\0';
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        // renderowanie podmenu dedykowanego pod szczegó³ow¹ konfiguracjê wybranego sprzêtu
        else if (current_state == GuiState::DeviceDetails && selected_device != nullptr) {
            int action = device_panel.render(selected_device);
            if (action == 1) { current_state = GuiState::Dashboard; selected_device = nullptr; }
            else if (action == 2) {
                // bezpieczne wyczyszczenie wskaŸnika przed fizycznym usuniêciem kontenera z pamiêci
                std::string name_to_remove = selected_device->getName();
                selected_device = nullptr; current_state = GuiState::Dashboard;
                hub.removeDevice(name_to_remove);
            }
        }
        ImGui::End();
        window.clear(sf::Color(30, 30, 40));
        ImGui::SFML::Render(window);
        window.display();
    }
}