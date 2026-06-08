#pragma once
#include "SmartLight.hpp"

class LightUI {
public:
    // W ImGui wystarczy jedna metoda renderuj¹ca i obs³uguj¹ca klikniêcia jednoczeœnie!
    void render(SmartLight* light);
};