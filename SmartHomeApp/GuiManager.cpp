#include "GuiManager.hpp"
#include "SmartHomeException.hpp"
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>

GuiManager::GuiManager(HomeManager& h, BinarySerializer& s, std::string filename)
    : hub(h), serializer(s), save_file(filename),
    current_state(GuiState::Dashboard),
    selected_device(nullptr),
    pending_device_type(AddDeviceType::None) {
    name_buffer[0] = '\0';
    pin_buffer[0] = '\0';
}

void GuiManager::run(sf::RenderWindow& window) {
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                serializer.saveToFile(hub, save_file);
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)window.getSize().x, (float)window.getSize().y));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Main UI", nullptr, window_flags);

        if (current_state == GuiState::Dashboard) {
            ImGui::Text("DASHBOARD SMART HOME");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("Twoje urzadzenia (kliknij, by zarzadzac):");
            ImGui::BeginChild("DeviceList", ImVec2(0, 500), true);

            for (const auto& device : hub.getDevices()) {
                std::string info = device->getDashboardInfo();

                // Logika kolorów: 
                // Zamek zamkniêty (czerwony)
                if (auto* lock = dynamic_cast<SmartLock*>(device.get())) {
                    ImGui::PushStyleColor(ImGuiCol_Text, lock->isLocked() ? ImVec4(1.0f, 0.2f, 0.2f, 1.0f) : ImVec4(0.2f, 1.0f, 0.2f, 1.0f));
                }
                // Reszta: Aktywne (zielone), nieaktywne (czerwone)
                else {
                    bool is_active = (info != "[OFF]" && info != "[GOTOWA]");
                    ImGui::PushStyleColor(ImGuiCol_Text, is_active ? ImVec4(0.2f, 1.0f, 0.2f, 1.0f) : ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
                }

                ImGui::Text(info.c_str());
                ImGui::PopStyleColor();
                ImGui::SameLine();

                if (ImGui::Selectable(device->getName().c_str())) {
                    selected_device = device.get();
                    current_state = GuiState::DeviceDetails;
                }
            }
            ImGui::EndChild();
            ImGui::Separator();

            // Przyklejenie przycisków na dole
            ImGui::SetCursorPosY(670);
            ImGui::Text("Dodaj nowe urzadzenie:");
            if (ImGui::Button("+ Lampa", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Light; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Termostat", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Thermostat; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Kamera", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Camera; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }
            ImGui::SameLine();
            if (ImGui::Button("+ Zamek", ImVec2(240, 40))) { pending_device_type = AddDeviceType::Lock; ImGui::OpenPopup("Konfiguracja Urzadzenia"); }

            // MODAL POP-UP (pozostaje bez zmian)
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
        else if (current_state == GuiState::DeviceDetails && selected_device != nullptr) {
            int action = device_panel.render(selected_device);
            if (action == 1) { current_state = GuiState::Dashboard; selected_device = nullptr; }
            else if (action == 2) {
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