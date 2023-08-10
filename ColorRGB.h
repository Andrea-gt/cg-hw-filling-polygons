// ColorRGB.h
#pragma once

class ColorRGB {
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;

    ColorRGB();
    ColorRGB(int red, int green, int blue);
    unsigned char clamp(int value);
    void printColor();
    ColorRGB operator+(const ColorRGB& other);
};