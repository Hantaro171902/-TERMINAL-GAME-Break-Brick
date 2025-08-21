#pragma once

#include <algorithm>

class Paddle {
public:
    int x, y, speed, delay, count_delay;
    char dir;
    int width = 9;  // Paddle width

    Paddle();
    void reset(int startX, int startY);
    void moveLeft(int minX);
    void moveRight(int maxX);
    void draw();
    void move();
};


