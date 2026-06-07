#include "SecurityCamera.hpp"

SecurityCamera::SecurityCamera(std::string name)
    : SmartDevice(name), is_recording(false), resolution("1080p") {
}

void SecurityCamera::turnOn() {
    setStatus(true);
    // Domyœlnie w³¹czamy nagrywanie przy starcie kamery
    startRecording();
}

void SecurityCamera::turnOff() {
    stopRecording();
    setStatus(false);
}

std::string SecurityCamera::getDeviceType() const {
    return "Kamera Bezpieczenstwa";
}

void SecurityCamera::startRecording() {
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