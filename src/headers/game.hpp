#pragma once

#include <vector>
#include "paddle.hpp"
#include "ball.hpp"
#include "brick_grid.hpp"
#include "ultils.hpp"

class Game {
public:
    int screenWidth;
    int screenHeight;
    int life;

    Paddle paddle;
    Ball ball;
    BrickGrid grid;

    // 2D map for rendering/collision similar to original
    std::vector<std::vector<int>> map; // 0 empty, 1 paddle, 2 brick, 5 ball, 7 top, 8 bottom, 9 side

    Game(int w, int h);

    void setup();
    void layout();
    void drawWalls();
    void drawPaddle();
    void drawBall();
    void drawBricks();

    void input();
    void update();
    void render();

    bool handleBallCollision(int nextX, int nextY);
    void gameOver();
};


