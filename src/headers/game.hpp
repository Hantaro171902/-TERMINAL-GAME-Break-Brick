#pragma once

#include <vector>
#include "paddle.hpp"
#include "ball.hpp"
#include "board.hpp"
#include "ultils.hpp"
#include "cursor_input.hpp"

class Game {
public:
    int screenWidth;
    int screenHeight;
    int life;
    bool decre_life;

    Paddle paddle;
    Ball ball;
    Board grid;

    // 2D map for rendering/collision
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


