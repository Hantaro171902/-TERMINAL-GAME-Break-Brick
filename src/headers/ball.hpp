#pragma once

class Ball {
public:
    int x, y, speed, dir;

    Ball();

    // void reset(int startX, int startY, int dirX, int dirY) {
    //     x = startX;
    //     y = startY;
    //     dx = dirX;
    //     dy = dirY;
    // }

    void draw();
    void move();
    bool collision(int fx, int fy);
    void bounce(int fx, int fy);
};


