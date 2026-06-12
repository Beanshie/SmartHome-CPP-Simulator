#pragma once

// Plik konfiguracyjny makr eksportu i importu dla biblioteki dynamicznej (DLL).
// Zarz¹dza widocznoœci¹ symboli kompilacji oraz wy³¹cza ostrze¿enia dotycz¹ce kontenerów biblioteki standardowej.

// Wy³¹czenie ostrze¿eñ MSVC o braku eksportu prywatnych sk³adowych bazuj¹cych na szablonach std
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)

// Makro warunkowe definiuj¹ce atrybut specyfikacji powi¹zania biblioteki dla kompilatora MSVC
#ifdef SMARTHOMECORE_EXPORTS
#define SMARTHOME_API __declspec(dllexport)
#else
#define SMARTHOME_API __declspec(dllimport)
#endif