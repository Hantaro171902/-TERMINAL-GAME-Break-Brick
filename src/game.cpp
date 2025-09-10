#include "game.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <locale>

using namespace std;

Game::Game(int w, int h)
    : screenWidth(w),
      screenHeight(h),
      life(5),
      paddle(w / 2, h - h / 7 - 1, w),   // Provide initial values
      ball(w / 2, h - h / 7 - 2)         // Provide initial values
{
    map.assign(screenHeight, vector<int>(screenWidth, 0));
}

void Game::setup() {
    srand((unsigned)time(nullptr));
    hideCursor();

    // Faster I/O and proper UTF-8 symbols
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setlocale(LC_ALL, "");

    paddle.width = 9;
    paddle.speed = 1;
    paddle.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 1);

    ball.speed = 1;
    int dirX = (random_range(0, 1) == 0) ? -1 : 1;
    int dirY = -1;
    ball.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 2, dirX, dirY);

    grid.loadHeartPattern();

    // Clear once at start
    clearScreen();
}

void Game::drawWalls() {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            if (j == 0 || j == screenWidth - 1) map[i][j] = 9; // side
            else if (i == 0) map[i][j] = 7; // top
            else if (i == screenHeight - 1) map[i][j] = 8; // bottom (life line)
            else map[i][j] = 0; // empty
        }
    }
}

void Game::drawPaddle() {
    for (int i = 0; i < paddle.width; ++i) {
        int px = paddle.x + i;
        if (px >= 0 && px < screenWidth) map[paddle.y][px] = 1;
    }
}

void Game::drawBall() {
    if (ball.x >= 0 && ball.x < screenWidth && ball.y >= 0 && ball.y < screenHeight)
        map[ball.y][ball.x] = 5;
}

void Game::drawBricks() {
    for (int r = 0; r < Board::rows; ++r) {
        for (int c = 0; c < Board::cols; ++c) {
            if (grid.bricks[r][c]) {
                int gx = grid.offsetX + c;
                int gy = grid.offsetY + r;
                if (gy >= 0 && gy < screenHeight && gx >= 0 && gx < screenWidth)
                    map[gy][gx] = 2;
            }
        }
    }
}

void Game::layout() {
    drawWalls();
    drawPaddle();
    drawBall();
    drawBricks();
}

bool Game::handleBallCollision(int nextX, int nextY) {
    // bottom -> lose life
    if (map[nextY][ball.x] == 8) {
        life--;
        paddle.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 1);
        ball.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 2, (random_range(0, 1) == 0 ? -1 : 1), -1);
        return true;
    }

    // walls and bricks and paddle
    bool collided = false;
    // Predict collisions on axes to decide bounce
    bool collideX = (map[ball.y][nextX] != 0);
    bool collideY = (map[nextY][ball.x] != 0);
    bool collideXY = (map[nextY][nextX] != 0);

    auto processHit = [&](int gx, int gy) {
        if (map[gy][gx] == 2) {
            grid.hitAt(gx, gy);
        }
    };

    if (collideX) { processHit(nextX, ball.y); collided = true; ball.dx = -ball.dx; }
    if (collideY) { processHit(ball.x, nextY); collided = true; ball.dy = -ball.dy; }
    if (!collideX && !collideY && collideXY) { processHit(nextX, nextY); collided = true; ball.dx = -ball.dx; ball.dy = -ball.dy; }

    return collided;
}

void Game::input() {
    InputKey key = getInputKey();
    switch (key) {
        case InputKey::LEFT:
            paddle.moveLeft(1);
            break;
        case InputKey::RIGHT:
            paddle.moveRight(screenWidth - 1);
            break;
        case InputKey::Q:
        case InputKey::ESC:
            life = 0;
            break;
        default:
            break;
    }
}

void Game::update() {
    // Move ball with collision
    int nextX = ball.x + ball.dx * ball.speed;
    int nextY = ball.y + ball.dy * ball.speed;

    // Check paddle collision manually (since map updated after drawPaddle())
    if (nextY == paddle.y && nextX >= paddle.x && nextX < paddle.x + paddle.width) {
        ball.dy = -1;
        // adjust dx based on where it hit the paddle
        int rel = nextX - paddle.x;
        if (rel < paddle.width / 3) ball.dx = -1;
        else if (rel > 2 * paddle.width / 3) ball.dx = 1;
    } else if (!handleBallCollision(nextX, nextY)) {
        ball.x = nextX;
        ball.y = nextY;
    }
}

void Game::render() {
    // Move cursor home and draw a single buffered frame to minimize I/O
    static const char* HOME = "\033[H";

    string frame;
    frame.reserve(static_cast<size_t>((screenWidth + 4) * (screenHeight + 4)) * 3);

    cout << HOME;

    // setTextColor(YELLOW);
    // cout << R"(
    //     ┏┓ ┏━┓┏━╸┏━┓╻┏    ┏━┓╻┏ ╻ ╻╻  ╻  
    //     ┣┻┓┣┳┛┣╸ ┣━┫┣┻┓   ┗━┓┣┻┓┃ ┃┃  ┃  
    //     ┗━┛╹┗╸┗━╸╹ ╹╹ ╹   ┗━┛╹ ╹┗━┛┗━╸┗━╸
    // )";
    // resetTextColor();
    

    frame += "LIFE: ";
    frame += to_string(life);
    frame += '\n';
    frame += '\n';

    cout << frame << fflush;

    for (int i = 0; i < screenHeight; ++i) {
        frame += "  "; // left padding
        for (int j = 0; j < screenWidth; ++j) {
            int v = map[i][j];
            if (i == 0 && j == 0) { frame += SYMBOL_DOUBLE_TOP_LEFT; continue; }
            if (i == 0 && j == screenWidth - 1) { frame += SYMBOL_DOUBLE_TOP_RIGHT; continue; }
            if (i == screenHeight - 1 && j == 0) { frame += SYMBOL_DOUBLE_BOTTOM_LEFT; continue; }
            if (i == screenHeight - 1 && j == screenWidth - 1) { frame += SYMBOL_DOUBLE_BOTTOM_RIGHT; continue; }

            if (v == 9) frame += SYMBOL_DOUBLE_VERTICAL;
            else if (v == 7 || v == 8) frame += SYMBOL_DOUBLE_HORIZONTAL;
            else if (v == 1) frame += BLOCK_RECT;       // paddle
            else if (v == 2) {
                frame += "\033[31m";
                frame += BLOCK_HALF; 
                frame += "\033[0m";
            }       // skull
            else if (v == 5) frame += 'o';              // ball
            else frame += ' ';
        }
        frame += '\n';
    }

    cout << HOME << frame << flush;
}

void Game::gameOver() {
    clearScreen();
    cout << " GAMEOVER ";
}


