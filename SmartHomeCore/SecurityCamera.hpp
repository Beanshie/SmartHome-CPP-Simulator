#pragma once
#include "SmartDevice.hpp"
#include <string>

class SMARTHOME_API SecurityCamera : public SmartDevice {
private:
    bool is_recording;
    std::string resolution; // np. "1080p", "4K"

public:
    SecurityCamera(std::string name);
    ~SecurityCamera() override = default;

    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Metody specyficzne dla kamery
    void startRecording();
    void stopRecording();
    bool isRecording() const;
    void setResolution(std::string res);

    std::string getDashboardInfo() const override;
};