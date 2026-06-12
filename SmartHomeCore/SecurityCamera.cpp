#include "SecurityCamera.hpp"

// Implementacja zachowañ i specyficznych metod dla kamery bezpieczeñstwa.
// Zarz¹dza automatyczn¹ aktywacj¹ zapisu wideo przy zmianach zasilania obiektu.

// Konstruktor klasy pochodnej inicjalizuj¹cy klasê bazow¹ oraz domyœlne parametry rejestracji.
SecurityCamera::SecurityCamera(std::string name)
    : SmartDevice(name), is_recording(false), resolution("1080p") {
}

// Funkcja w³¹czaj¹ca zasilanie urz¹dzenia i wymuszaj¹ca natychmiastowe rozpoczêcie zapisu wideo.
void SecurityCamera::turnOn() {
    setStatus(true);
    is_recording = true;
}

// Funkcja bezpiecznie odcinaj¹ca zasilanie po uprzednim przerwaniu zapisu strumieniowego.
void SecurityCamera::turnOff() {
    stopRecording();
    setStatus(false);
}

// Funkcja zwracaj¹ca sta³y identyfikator tekstowy podtypu urz¹dzenia dla celów polimorficznych.
std::string SecurityCamera::getDeviceType() const {
    return "Kamera Bezpieczenstwa";
}

// Funkcja uruchamiaj¹ca nagrywanie, pod warunkiem, ¿e urz¹dzenie jest aktualnie zasilane.
void SecurityCamera::startRecording() {
    if (isOn()) {
        is_recording = true;
    }
}

// Funkcja zatrzymuj¹ca proces rejestracji wideo bez wy³¹czania g³ównego zasilania kamery.
void SecurityCamera::stopRecording() {
    is_recording = false;
}

// Funkcja zwracaj¹ca flagê okreœlaj¹c¹ bie¿¹cy stan rejestratora obrazu.
bool SecurityCamera::isRecording() const {
    return is_recording;
}

// Funkcja zmieniaj¹ca w³aœciwoœæ rozdzielczoœci przechwytywanego strumienia danych.
void SecurityCamera::setResolution(std::string res) {
    resolution = res;
}

// Funkcja generuj¹ca zwiêz³y token statusowy widoczny na liœcie urz¹dzeñ w menu g³ównym.
std::string SecurityCamera::getDashboardInfo() const {
    return isRecording() ? "[REC]" : "[GOTOWA]";
}