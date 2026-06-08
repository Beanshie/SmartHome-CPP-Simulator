#include "SecurityCamera.hpp"

SecurityCamera::SecurityCamera(std::string name)
    : SmartDevice(name), is_recording(false), resolution("1080p") {
}

void SecurityCamera::turnOn() {
    setStatus(true);
    is_recording = true; // Wymuszamy start, bo skoro wchodzimy w turnOn, to kamera ma dzia³aæ
}

void SecurityCamera::turnOff() {
    stopRecording();
    setStatus(false);
}

std::string SecurityCamera::getDeviceType() const {
    return "Kamera Bezpieczenstwa";
}

void SecurityCamera::startRecording() {
    // Tutaj zostawiamy sprawdzenie, bo to jest metoda "u¿ytkowa"
    if (isOn()) {
        is_recording = true;
    }
}

void SecurityCamera::stopRecording() {
    is_recording = false;
}

bool SecurityCamera::isRecording() const {
    return is_recording;
}

void SecurityCamera::setResolution(std::string res) {
    resolution = res;
}

std::string SecurityCamera::getDashboardInfo() const {
    return isRecording() ? "[REC]" : "[GOTOWA]";
}