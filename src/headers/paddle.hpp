#pragma once

#include <algorithm>

class Paddle {
public:
    int x, y, speed, delay, count_delay;
    char dir;

    Paddle();
    void draw();
    void move();

};


