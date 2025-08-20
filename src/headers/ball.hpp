#pragma once

class Ball {
public:
    int x;
    int y;
    int dx;
    int dy;
    int speed;

    Ball() : x(0), y(0), dx(1), dy(-1), speed(1) {}

    void reset(int startX, int startY, int dirX, int dirY) {
        x = startX;
        y = startY;
        dx = dirX;
        dy = dirY;
    }
};


