#pragma once

#pragma warning(disable: 4251)
#pragma warning(disable: 4275)

#ifdef SMARTHOMECORE_EXPORTS
#define SMARTHOME_API __declspec(dllexport)
#else
#define SMARTHOME_API __declspec(dllimport)
#endif