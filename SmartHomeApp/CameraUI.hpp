#pragma once
#include "SecurityCamera.hpp"

// widok interfejsu dla kamery monitoringu. odpowiada za wyswietlanie 
// statusu nagrywania i przyciskow akcji w imgui.
class CameraUI {
public:
    // gui tylko operuje na obiekcie, wiec uzywamy zwyklego wskaznika
    void render(SecurityCamera* cam);
};