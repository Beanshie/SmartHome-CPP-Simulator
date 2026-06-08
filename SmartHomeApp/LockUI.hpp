#pragma once
#include "SmartLock.hpp"
#include <string>

class LockUI {
private:
    // ImGui potrzebuje zwyk³ej tablicy charów (bufora) do wpisywania tekstu
    char pin_buffer[16] = "";
    std::string error_message = "";

public:
    void render(SmartLock* lock);
    void reset();
};