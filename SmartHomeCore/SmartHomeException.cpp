#include "SmartHomeException.hpp"

// Inicjalizujemy zmienn¹ 'message' na liœcie inicjalizacyjnej konstruktora
SmartHomeException::SmartHomeException(const std::string& msg)
    : message(msg) {
}

// Zwracamy nasz¹ wiadomoœæ jako klasyczn¹ tablicê znaków (wymóg standardu C++)
const char* SmartHomeException::what() const noexcept {
    return message.c_str();
}