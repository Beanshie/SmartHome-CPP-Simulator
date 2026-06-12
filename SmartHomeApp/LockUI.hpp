#pragma once
#include "SmartLock.hpp"
#include <string>

// widok odpowiedzialny za obs³ugê zamka elektronicznego.
// trzyma wewn¹trz wpisywany pin i b³êdy, ¿eby nie znika³y miêdzy klatkami.
class LockUI {
private:
    // bufor dla imgui na wpisywanie znaków z klawiatury
    char pin_buffer[16] = "";
    std::string error_message = "";

public:
    void render(SmartLock* lock);

    // czyszczenie okna przy powrocie do g³ównego menu
    void reset();
};