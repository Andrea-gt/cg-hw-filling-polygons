// ColorRGB.cpp
#include "ColorRGB.h"
#include <iostream>

ColorRGB::ColorRGB() : r(0), g(0), b(0) {}

ColorRGB::ColorRGB(int red, int green, int blue) {
    r = clamp(red);
    g = clamp(green);
    b = clamp(blue);
}

unsigned char ColorRGB::clamp(int value) {
    if (value < 0)
        return 0;
    else if (value > 255)
        return 255;
    else
        return static_cast<unsigned char>(value);
}

void ColorRGB::printColor() {
    std::cout << "RGB: (" << static_cast<int>(r) << ", "
              << static_cast<int>(g) << ", " << static_cast<int>(b) << ")" << std::endl;
}

ColorRGB ColorRGB::operator+(const ColorRGB& other) {
    int sum_r = static_cast<int>(r) + static_cast<int>(other.r);
    int sum_g = static_cast<int>(g) + static_cast<int>(other.g);
    int sum_b = static_cast<int>(b) + static_cast<int>(other.b);

    return ColorRGB(sum_r, sum_g, sum_b);
}
