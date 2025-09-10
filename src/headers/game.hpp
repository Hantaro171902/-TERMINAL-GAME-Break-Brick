#pragma once

#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <memory>
#include "paddle.hpp"
#include "ball.hpp"
#include "brick.hpp"
#include "utils.hpp"
#include "cursor_input.hpp"

class Game {
public:
    Game(int width, int height);
    ~Game();    // add a destructor to clean up terminal settings
    void setup();
    void run();

private:
    
    // Core game loop pieces
    void processInput();
    void update(float deltaTime);
    void render();
    void resetBall();
    void drawWalls() const;
    void drawBricks() const;
    void drawTitle() const;
    void gameOver();

    // Game objects
    Paddle paddle;
    Ball ball;
    Brick grid;

    // Settings
    const int width;
    const int height;
    int life = 0; 
    bool running = true;

    // Score 
    // int score = 0;

};


