#pragma once
#include "SmartDevice.hpp"
#include <string>

// Klasa reprezentuj¹ca inteligentn¹ kamerê bezpieczeñstwa.
// Rozszerza podstawowe urz¹dzenie o obs³ugê rejestracji strumienia wideo oraz konfiguracjê rozdzielczoœci.

class SMARTHOME_API SecurityCamera : public SmartDevice {
private:
    bool is_recording;
    std::string resolution; // np. "1080p", "4K"

public:
    SecurityCamera(std::string name);
    ~SecurityCamera() override = default;

    // Nadpisane metody polimorficzne zarz¹dzania zasilaniem i identyfikacji typu.
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Uruchomienie zapisu wideo (wymaga wczeœniejszego w³¹czenia zasilania urz¹dzenia).
    void startRecording();

    // Zatrzymanie aktywnego procesu rejestracji obrazu.
    void stopRecording();

    // Sprawdzenie, czy kamera aktualnie zapisuje materia³ na dysku.
    bool isRecording() const;

    // Zmiana domyœlnego trybu jakoœci przechwytywanego obrazu.
    void setResolution(std::string res);

    // Wygenerowanie skróconego statusu urz¹dzenia na potrzeby g³ównego pulpitu GUI.
    std::string getDashboardInfo() const override;
};