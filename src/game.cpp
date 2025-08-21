#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game(int w, int h) : screenWidth(w), screenHeight(h), life(5) {
    map.assign(screenHeight, std::vector<int>(screenWidth, 0));
}

void Game::setup() {
    srand((unsigned)time(nullptr));
    hideCursor();
    paddle.width = 9;
    paddle.speed = 1;
    paddle.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 1);

    ball.speed = 1;
    int dirX = (random_range(0, 1) == 0) ? -1 : 1;
    int dirY = -1;
    ball.reset(screenWidth / 2, screenHeight - screenHeight / 7 - 2, dirX, dirY);

    grid.loadHeartPattern();
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
    for (int r = 0; r < grid.rows; ++r) {
        for (int c = 0; c < grid.cols; ++c) {
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
    if (kbhit()) {
        int ch = getch();
        // Windows arrow keys come as 224 then code; on Linux we may get escape sequences.
        if (ch == 27) { // ESC sequence
            if (kbhit()) {
                getch(); // '['
                int code = getch();
                if (code == 'D') paddle.moveLeft(1); // left
                else if (code == 'C') paddle.moveRight(screenWidth - 1); // right
            }
        } else if (ch == 75) {
            paddle.moveLeft(1);
        } else if (ch == 77) {
            paddle.moveRight(screenWidth - 1);
        } else if (ch == 'q' || ch == 'Q') {
            life = 0;
        }
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
    move_cursor(2, 1);
    std::cout << "LIFE: " << life;

    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            move_cursor(j + 2, i + 3);
            int v = map[i][j];
            if (v == 9 || v == 7) std::cout << (char)219;
            else if (v == 8) std::cout << (char)240;
            else if (v == 1) std::cout << (char)219;
            else if (v == 2) std::cout << (char)233;
            else if (v == 5) std::cout << (char)254;
            else std::cout << ' ';
        }
    }
}

void Game::gameOver() {
    clearScreen();
    std::cout << " GAMEOVER ";
}


