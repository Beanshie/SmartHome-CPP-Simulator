#include <iostream>
#include <memory>

// Do³¹czamy tylko to, co niezbêdne w mainie
#include "HomeManager.hpp"
#include "BinarySerializer.hpp"
#include "GuiManager.hpp"
#include "SmartLight.hpp"
#include "Thermostat.hpp"
#include "SecurityCamera.hpp"
#include "SmartLock.hpp"

int main() {
    std::string config_file = "smarthome_save.bin";

    HomeManager hub;
    BinarySerializer serializer;

    // Próba wczytania stanu
    serializer.loadFromFile(hub, config_file);

    // Domyœlne urz¹dzenia, jeœli plik by³ pusty/nie istnia³
    if (hub.getDevices().empty()) {
        hub.addDevice(std::make_unique<SmartLight>("Lampa w Salonie"));
        hub.addDevice(std::make_unique<Thermostat>("Termostat na Parterze"));
        hub.addDevice(std::make_unique<SecurityCamera>("Kamera przed domem"));
        hub.addDevice(std::make_unique<SmartLock>("Zamek Drzwi", "1234"));
    }

    // Uruchamiamy nasz nowy TUI!
    GuiManager gui(hub, serializer, config_file);
    gui.run();

    return 0;
}