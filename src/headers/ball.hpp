#pragma once

class Ball {
public:
    int x, y, speed, dir;
    int dx, dy;  // Direction vectors

    Ball();

    void reset(int startX, int startY, int dirX, int dirY);

    void draw();
    void move();
    bool collision(int fx, int fy);
    void bounce(int fx, int fy);
};


