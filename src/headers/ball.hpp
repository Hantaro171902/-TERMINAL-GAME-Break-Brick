#pragma once

#include "game_object.hpp"

class Ball : public GameObject {
public:
    int dx, dy;
    int speed;

    Ball(int startX, int startY);

    void reset(int startX, int startY, int dirX, int dirY);
    void update() override;
    void draw() override;
    void bounceX();
    void bounceY();

    int getNextX() const { return x + dx; }
    int getNextY() const { return y + dy; }
};