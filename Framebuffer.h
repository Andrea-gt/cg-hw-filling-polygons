// Framebuffer.h
#pragma once

#include <vector>
#include <string> // Add this line to include <string>
#include <fstream> // Add this line to include <fstream>
#include "ColorRGB.h"
#include "Vertex2.h"

class Framebuffer {
public:
    Framebuffer(int width, int height);
    void clear();
    void setCurrentColor(ColorRGB myColor);
    void point(Vertex2 myVertex);
    void drawLine(Vertex2 start, Vertex2 end);
    void drawPolygon(const std::vector<Vertex2>& points);
    void fillPolygon(const std::vector<Vertex2>& points);
    void render();
    void writeBMP(const std::string& filename);

private:
    int width;
    int height;
    std::vector<ColorRGB> framebuffer;
    ColorRGB clearColor;
    ColorRGB currentColor;
};
