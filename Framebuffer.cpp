// Framebuffer.cpp
#include "Framebuffer.h"
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iostream>

Framebuffer::Framebuffer(int width, int height) : width(width), height(height), framebuffer(width * height) {
    clearColor = ColorRGB(0, 0, 0);
    currentColor = ColorRGB(0, 0, 0);
}

void Framebuffer::clear() {
    for (size_t i = 0; i < framebuffer.size(); ++i) {
        framebuffer[i] = clearColor;
    }
}

void Framebuffer::setCurrentColor(ColorRGB myColor) {
    currentColor = myColor;
}

void Framebuffer::point(Vertex2 myVertex) {
    if (myVertex.x >= 0 && myVertex.x < width && myVertex.y >= 0 && myVertex.y < height) {
        framebuffer[(width * myVertex.y) + myVertex.x] = currentColor;
    }
}

void Framebuffer::drawLine(Vertex2 start, Vertex2 end) {
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        point(start);

        if (start.x == end.x && start.y == end.y) {
            break;
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            start.x += sx;
        }

        if (err2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

void Framebuffer::drawPolygon(const std::vector<Vertex2>& points) {
    if (points.size() < 2) {
        return;
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        drawLine(points[i], points[i + 1]);
    }

    drawLine(points.back(), points.front());
}

void Framebuffer::fillPolygon(const std::vector<Vertex2>& points) {
    if (points.size() < 3) {
        return;
    }

    int minY = height;
    int maxY = 0;

    for (const auto& vertex : points) {
        minY = std::min(minY, vertex.y);
        maxY = std::max(maxY, vertex.y);
    }

    for (int y = minY; y <= maxY; y++) {
        std::vector<int> intersections;

        for (size_t i = 0; i < points.size(); i++) {
            size_t nextIndex = (i + 1) % points.size();
            const Vertex2& current = points[i];
            const Vertex2& next = points[nextIndex];

            if ((current.y <= y && next.y > y) || (next.y <= y && current.y > y)) {
                int xIntersection = current.x + (y - current.y) * (next.x - current.x) / (next.y - current.y);
                intersections.push_back(xIntersection);
            }
        }

        std::sort(intersections.begin(), intersections.end());

        for (size_t i = 0; i < intersections.size(); i += 2) {
            int startX = intersections[i];
            int endX = intersections[i + 1];

            if (startX > endX) {
                std::swap(startX, endX);
            }

            for (int x = startX; x <= endX; x++) {
                point({ x, y });
            }
        }
    }
}

void Framebuffer::render() {
    clear();

    ColorRGB lineColor(255, 255, 255);
    setCurrentColor(lineColor);

    // Polygon 1
    std::vector<Vertex2> polygonPoints = {
            {165, 380}, {185, 360},
            {180, 330}, {207, 345},
            {233, 330}, {230, 360},
            {250, 380}, {220, 385},
            {205, 410}, {193, 383}
    };

    drawPolygon(polygonPoints);

    ColorRGB fillColor(189, 246, 252);
    setCurrentColor(fillColor);

    fillPolygon(polygonPoints);

    // Polygon 2
    std::vector<Vertex2> polygonPoints2 = {
            {321, 335}, {288, 286},
            {339, 251}, {374, 302}
    };

    drawPolygon(polygonPoints2);

    ColorRGB fillColor2(249, 222, 169);
    setCurrentColor(fillColor2);

    fillPolygon(polygonPoints2);


    // Polygon 3
    std::vector<Vertex2> polygonPoints3 = {
            {377, 249}, {411, 197}, {436, 249}
    };

    drawPolygon(polygonPoints3);

    ColorRGB fillColor3(200, 152, 252);
    setCurrentColor(fillColor3);

    fillPolygon(polygonPoints3);


    // Polygon 4
    std::vector<Vertex2> polygonPoints4 = {
            {413, 177}, {448, 159}, {502, 88}, {553, 53},
            {535, 36}, {676, 37}, {660, 52}, {750, 145},
            {761, 179}, {672, 192}, {659, 214}, {615, 214},
            {632, 230}, {580, 230}, {597, 215}, {552, 214},
            {517, 144}, {466, 180}
    };

    drawPolygon(polygonPoints4);

    ColorRGB fillColor4(222, 244, 208);
    setCurrentColor(fillColor4);
    fillPolygon(polygonPoints4);

    // Polygon 5
    std::vector<Vertex2> polygonPoints1 = {
            {682, 175}, {708, 120}, {735, 148}, {739, 170}
    };

    setCurrentColor(clearColor);
    fillPolygon(polygonPoints1);

    writeBMP("out.bmp");
}

void Framebuffer::writeBMP(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    // BMP file header
    unsigned char fileHeader[] = {
            'B', 'M',  // Signature
            0, 0, 0, 0, // File size (will be filled later)
            0, 0,      // Reserved
            0, 0,      // Reserved
            54, 0, 0, 0 // Pixel data offset
    };

    // BMP info header
    unsigned char infoHeader[] = {
            40, 0, 0, 0,  // Info header size
            0, 0, 0, 0,   // Image width (will be filled later)
            0, 0, 0, 0,   // Image height (will be filled later)
            1, 0,         // Number of color planes
            24, 0,        // Bits per pixel (3 bytes)
            0, 0, 0, 0,   // Compression method
            0, 0, 0, 0,   // Image size (will be filled later)
            0, 0, 0, 0,   // Horizontal resolution (pixels per meter, not used)
            0, 0, 0, 0,   // Vertical resolution (pixels per meter, not used)
            0, 0, 0, 0,   // Number of colors in the palette (not used)
            0, 0, 0, 0    // Number of important colors (not used)
    };

    // Calculate some values
    int imageSize = width * height * 3;  // 3 bytes per pixel (BGR)
    int fileSize = imageSize + sizeof(fileHeader) + sizeof(infoHeader);

    // Fill in the file header
    *(int*)&fileHeader[2] = fileSize;          // File size
    *(int*)&fileHeader[10] = sizeof(fileHeader) + sizeof(infoHeader);  // Pixel data offset

    // Fill in the info header
    *(int*)&infoHeader[4] = width;
    *(int*)&infoHeader[8] = height;
    *(int*)&infoHeader[20] = imageSize;

    // Write the headers to the file
    file.write(reinterpret_cast<char*>(fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(infoHeader), sizeof(infoHeader));

    // Write the pixel data
    file.write(reinterpret_cast<char*>(framebuffer.data()), imageSize);

    // Close the file
    file.close();
}
