#pragma once
#include <iostream>
enum class Color {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Gray = 90,
    Reset = 0
};

inline void setColor(Color c) {
    printf("\033[%dm", static_cast<int>(c));
    std::cout << "\033[" << static_cast<int>(c) << "m";
}

inline void resetColor() {
    std::cout << "\033[0m";
}