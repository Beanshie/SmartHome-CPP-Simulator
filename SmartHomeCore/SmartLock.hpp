#pragma once
#include "SmartDevice.hpp"
#include <string>

class SMARTHOME_API SmartLock : public SmartDevice {
private:
    bool is_locked;
    std::string pin_code;

public:
    SmartLock(std::string name, std::string pin);
    ~SmartLock() override = default;

    // W przypadku zamka, "turnOn" mo¿e oznaczaæ aktywacjê systemu ryglowania
    void turnOn() override;
    void turnOff() override;
    std::string getDeviceType() const override;

    // Metody specyficzne dla zamka
    void lock();
    void unlock(std::string entered_pin); // Tu bêdziemy rzucaæ wyj¹tek!
    bool isLocked() const;
};