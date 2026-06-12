# 🏠 Smart Home System (JIPP Project)

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![ImGui](https://img.shields.io/badge/UI-Dear%20ImGui-red.svg)](https://github.com/ocornut/imgui)
[![SFML](https://img.shields.io/badge/Graphics-SFML-green.svg)](https://www.sfml-dev.org/)

An advanced desktop application simulating a smart home management system. The project was developed as part of the JIPP course, with a strong emphasis on **modern C++**, **Object-Oriented Programming (OOP)**, and **clean architecture**.

## ✨ Key Features

The system offers a centralized Dashboard allowing users to add, remove, and manage smart devices:
* 💡 **Smart Light** - power control and smooth brightness adjustment (+/- 10%).
* 🌡️ **Thermostat** - precise temperature control with safe range validation (10-40°C).
* 📷 **Security Camera** - independent power management and continuous recording mode.
* 🔒 **Smart Lock** - electronic lock requiring authorization with a custom PIN code.
* 🌐 **Network Diagnostics** - built-in module for simulating device pinging and reading hidden MAC addresses.

## 🛠️ Architecture & Design Patterns

The project is divided into a **dynamic library (DLL)** containing the business logic (`SmartHomeCore`) and a **client application** handling the user interface (`SmartHomeApp`). 

Key technological solutions:
* **Polymorphism & Abstraction:** The GUI communicates with devices through the virtual base class `SmartDevice`, eliminating the need to modify views when adding new device types (Open/Closed Principle compliance).
* **Memory Safety:** No manual memory management (`new`/`delete`). The project relies entirely on smart pointers (`std::unique_ptr`) to prevent memory leaks.
* **Encapsulation & Friend Class:** Protection of sensitive data (e.g., PIN codes, MAC addresses), accessible only to the dedicated diagnostic system via a friend class declaration.
* **Custom Exception Handling:** Logic validation (e.g., attempting to use a powered-off device or entering a wrong PIN) is implemented by throwing and catching custom `SmartHomeException` objects.
* **Binary Serialization:** The system state (including hidden passwords and specific parameters) is seamlessly saved and loaded in the background using binary streams (`std::ios::binary`).

## 🚀 Technologies

* **Language:** C++ (Standard 17)
* **Graphics Library:** SFML (Simple and Fast Multimedia Library)
* **User Interface:** Dear ImGui (Immediate Mode GUI)
* **Compiler:** MSVC (Visual Studio) / GCC

## ⚙️ How to Run

1. Clone the repository to your local drive.
2. Open the solution file (`.sln`) in Visual Studio.
3. Ensure the build configuration is set to **x64** (Debug or Release).
4. Build and run the `SmartHomeApp` project. 