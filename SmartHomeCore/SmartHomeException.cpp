#include "SmartHomeException.hpp"

// Implementacja niestandardowej klasy wyj¹tków dla ekosystemu smart home.
// Zapewnia bezpieczne dla pamiêci przekazywanie komunikatów o b³êdach zgodne z interfejsem biblioteki standardowej.

// Konstruktor przepisuj¹cy przekazany komunikat b³êdu do wewnêtrznego obiektu typu std::string.
SmartHomeException::SmartHomeException(const std::string& msg)
    : message(msg) {
}

// Bezwyj¹tkowa funkcja zwracaj¹ca wskaŸnik na sta³y ci¹g znaków jêzyka C z opisem b³êdu.
const char* SmartHomeException::what() const noexcept {
    return message.c_str();
}