#include "game.hpp"
#include "color.hpp"
#include "utils.hpp"
#include "brick.hpp"
#include "cursor_input.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>

using namespace std;

Game::Game(int w, int h)
    : width(w)
    , height(h)
    , life(5)
    , paddle(w / 2, h - h / 7 - 1, 9, 1, BLOCK_RECT)   // Provide initial values (length=9, thickness=1)
    , ball(w / 2, h - h / 7 - 2, 1, 1, BALL_SOLID)      // Provide initial values (width=1, height=1)
{
    paddle.setWindowLimits(width, height);
    ball.setWindowLimits(width, height);

    // Color 
    paddle.setColor(TextColor::CYAN);
    ball.setColor(TextColor::YELLOW);

    clearScreen();
    hideCursor();
}


Game::~Game() {
    showCursor();
    resetTextColor();
    clearScreen();
}

void Game::run() {
    srand((unsigned)time(nullptr));
    // Time tracking for smoother movement
    auto prevTime = chrono::high_resolution_clock::now();

    while (running) {
        auto currentTime = chrono::high_resolution_clock::now();
        float deltaTime = chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;

        processInput();
        update(deltaTime); // Pass deltaTime to update
        render();

        this_thread::sleep_for(chrono::milliseconds(20)); // Adjust for desired frame rate
    }
}

// void Game::setup() {
//     srand((unsigned)time(nullptr));
//     hideCursor();

//     // Faster I/O and proper UTF-8 symbols
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     setlocale(LC_ALL, "");

//     paddle.width = 9;
//     paddle.speed = 1;
//     paddle.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 1);

//     ball.speed = 1;
//     int dirX = (random_range(0, 1) == 0) ? -1 : 1;
//     int dirY = -1;
//     ball.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 2, dirX, dirY);

//     grid.loadHeartPattern();

//     // Clear once at start
//     clearScreen();
// }

void Game::drawWalls() const {
    // Draw boundary walls using double line characters
    setTextColor(TextColor::WHITE);
    // Top wall
    move_cursor(0, 0);
    cout << SYMBOL_DOUBLE_TOP_LEFT;
    for (int i = 1; i < width - 1; ++i) cout << SYMBOL_DOUBLE_HORIZONTAL;
    cout << SYMBOL_DOUBLE_TOP_RIGHT;

    // Side walls
    for (int i = 1; i < height - 1; ++i) {
        move_cursor(0, i);
        cout << SYMBOL_DOUBLE_VERTICAL;
        move_cursor(width - 1, i);
        cout << SYMBOL_DOUBLE_VERTICAL;
        // Removed undefined y and board usage
    }

    // Bottom wall
    move_cursor(0, height - 1);
    cout << SYMBOL_DOUBLE_BOTTOM_LEFT;
    for (int i = 1; i < width - 1; ++i) cout << SYMBOL_DOUBLE_HORIZONTAL;
    cout << SYMBOL_DOUBLE_BOTTOM_RIGHT;

    resetTextColor();
}

// void Game::drawPaddle() {
//     for (int i = 0; i < paddle.width; ++i) {
//         int px = paddle.x + i;
//         if (px >= 0 && px < screenWidth) map[paddle.y][px] = 1;
//     }
// }

// void Game::drawBall() {
//     if (ball.x >= 0 && ball.x < screenWidth && ball.y >= 0 && ball.y < screenHeight)
//         map[ball.y][ball.x] = 5;
// }

// void Game::drawBricks() {
//     for (int r = 0; r < Board::rows; ++r) {
//         for (int c = 0; c < Board::cols; ++c) {
//             if (grid.bricks[r][c]) {
//                 int gx = grid.offsetX + c;
//                 int gy = grid.offsetY + r;
//                 if (gy >= 0 && gy < screenHeight && gx >= 0 && gx < screenWidth)
//                     map[gy][gx] = 2;
//             }
//         }
//     }
// }

// void Game::layout() {
//     drawWalls();
//     drawPaddle();
//     drawBall();
//     drawBricks();
// }


void Game::processInput() {
    InputKey key = getInputKey();

    // Reset velocities
    paddle.setVelocityY(0.0f);
    paddle.setVelocityY(0.0f);

    switch (key) {
        case InputKey::UP:
            paddle.moveUp();
            break;
        case InputKey::DOWN:
            paddle.moveDown();
            break;
        case InputKey::LEFT:
            paddle.moveLeft();
            break;
        case InputKey::RIGHT:
            paddle.moveRight();
            break;
        case InputKey::Q:
        case InputKey::ESC:
            running = false;
            break;
        default:
            break;
    }
}


// bool Game::handleBallCollision(int nextX, int nextY) {
//     // bottom -> lose life
//     if (map[nextY][ball.x] == 8) {
//         life--;
//         paddle.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 1);
//         ball.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 2, (random_range(0, 1) == 0 ? -1 : 1), -1);
//         return true;
//     }

//     // walls and bricks and paddle
//     bool collided = false;
//     // Predict collisions on axes to decide bounce
//     bool collideX = (map[ball.y][nextX] != 0);
//     bool collideY = (map[nextY][ball.x] != 0);
//     bool collideXY = (map[nextY][nextX] != 0);

//     auto processHit = [&](int gx, int gy) {
//         if (map[gy][gx] == 2) {
//             grid.hitAt(gx, gy);
//         }
//     };

//     if (collideX) { processHit(nextX, ball.y); collided = true; ball.dx = -ball.dx; }
//     if (collideY) { processHit(ball.x, nextY); collided = true; ball.dy = -ball.dy; }
//     if (!collideX && !collideY && collideXY) { processHit(nextX, nextY); collided = true; ball.dx = -ball.dx; ball.dy = -ball.dy; }

//     return collided;
// }

// void Game::input() {
//     InputKey key = getInputKey();
//     switch (key) {
//         case InputKey::LEFT:
//             paddle.moveLeft(1);
//             break;
//         case InputKey::RIGHT:
//             paddle.moveRight(screenWidth - 1);
//             break;
//         case InputKey::Q:
//         case InputKey::ESC:
//             life = 0;
//             break;
//         default:
//             break;
//     }
// }

void Game::update(float deltaTime) {
    paddle.update(deltaTime);
    ball.updateBall(paddle, width, height);

    XYPosition ballPos = ball.getPosition();

    if (ballPos.y >= height - 1) {
        life--;
        // paddle.reset(width / 2, height - height / 7 - 1);
        ball.reset(width / 2, height - height / 7 - 2);
        if (life <= 0) {
            running = false;
            gameOver();
        }
    }
    

    // Move ball with collision
    // int nextX = ball.x + ball.dx * ball.speed;
    // int nextY = ball.y + ball.dy * ball.speed;

    // // Check paddle collision manually (since map updated after drawPaddle())
    // if (nextY == paddle.y && nextX >= paddle.x && nextX < paddle.x + paddle.width) {
    //     ball.dy = -1;
    //     // adjust dx based on where it hit the paddle
    //     int rel = nextX - paddle.x;
    //     if (rel < paddle.width / 3) ball.dx = -1;
    //     else if (rel > 2 * paddle.width / 3) ball.dx = 1;
    // } else if (!handleBallCollision(nextX, nextY)) {
    //     ball.x = nextX;
    //     ball.y = nextY;
    // }
}

void Game::drawBricks() const {
    // Draw the bricks pattern inside the wall boundary using the Brick class
    for (int i = 0; i < grid.rows; ++i) {
        for (int j = 0; j < grid.cols; ++j) {
            if (grid.bricks[i][j]) {
                int x = grid.offsetX + j;
                int y = grid.offsetY + i;
                // Only draw if inside the wall boundary
                if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
                    move_cursor(x, y);
                    setTextColor(TextColor::RED);
                    cout << BLOCK_HALF;
                    resetTextColor();
                }
            }
        }
    }
}

void Game::render() {
    clearTerminal();
    drawWalls();
    drawBricks();
    paddle.clear();
    ball.clear();
    paddle.draw();
    ball.draw();
    move_cursor(width / 2 - 5, 1);
    setTextColor(TextColor::WHITE);
    cout << "LIFE: " << life;
    resetTextColor();
    cout.flush();
}

void Game::drawTitle() const {
    move_cursor(width / 2 - 5, 2); 
    setTextColor(TextColor::YELLOW);
    cout << R"(
            ┏┓ ┏━┓┏━╸┏━┓╻┏    ┏━┓╻┏ ╻ ╻╻  ╻  
            ┣┻┓┣┳┛┣╸ ┣━┫┣┻┓   ┗━┓┣┻┓┃ ┃┃  ┃  
            ┗━┛╹┗╸┗━╸╹ ╹╹ ╹   ┗━┛╹ ╹┗━┛┗━╸┗━╸
    )";

    resetTextColor();
}

void Game::resetBall() {
    ball.reset(width / 2, height - height / 7 - 2);
}

void Game::gameOver() {
    clearScreen();
    move_cursor(width / 2 - 5, height / 2);
    setTextColor(TextColor::RED);
    if (life <= 0) {
        cout << " YOU LOSE! ";
    }
    else {
        cout << " YOU WIN! ";
    }
    resetTextColor();
}


