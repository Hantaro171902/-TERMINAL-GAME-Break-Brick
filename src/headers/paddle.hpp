#pragma once

#include <algorithm>
#include "game_object.hpp"
#include "cursor_input.hpp"


class Paddle : public GameObject {
public:
    int width;
    int speed;

    Paddle(int startX, int startY, int gameWidth);


    void update() override;
    void draw() override;

    void processInput(char input);

    // Add missing methods
    void reset(int newX, int newY) { x = newX; y = newY; }
    void moveLeft(int minX) { if (x > minX) --x; }
    void moveRight(int maxX) { if (x + width < maxX) ++x; }

private:
    const int gameWidth;
};


