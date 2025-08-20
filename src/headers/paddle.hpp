#pragma once

#include <algorithm>

class Paddle {
public:
    int x;
    int y;
    int width;
    int speed;

    Paddle() : x(0), y(0), width(9), speed(1) {}

    void reset(int centerX, int yPosition) {
        y = yPosition;
        x = centerX - width / 2;
    }

    void moveLeft(int minX) {
        x = std::max(minX, x - speed);
    }

    void moveRight(int maxX) {
        x = std::min(maxX - width, x + speed);
    }
};


