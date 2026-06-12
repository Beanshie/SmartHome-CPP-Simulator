#pragma once
#include "SmartLight.hpp"

// interfejs dla inteligentnej lampki. prosty widok bez wewnetrznego stanu,
// bo wszystko czego potrzebujemy jest juz w samym obiekcie swiatla.
class LightUI {
public:
    // imgui zalatwia rysowanie i sprawdzanie klikniec w jednym przebiegu
    void render(SmartLight* light);
};