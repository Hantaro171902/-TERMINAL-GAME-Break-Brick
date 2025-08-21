#include "board.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "game.hpp"
#include "ultils.hpp"
#include <iostream>

using namespace std;

Paddle paddle;
Ball ball;

void Board::heart() {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            bricks[i][j] = (heart[i][j] == '#') ? 1 : 0;
        }
    }
}

void Board::brick() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (bricks[i][j] == 1) {
                Game.map[i + 2][j + 6] = 2; // Adjusting position for rendering
            }
        }
    }
}

void Board::wall() {
    for (int i = 0; i < Game.screenHeight; i++) {
        for (int j = 0; j < Game.screenWidth; j++) {
            if (j == 0 || j == Game.screenWidth - 1) Game.map[i][j] = 9;
            else if (i == 0) map[i][j] = 7;
            else if (i == Game.screenHeight - 1) Game.map[i][j] = 8;
            else Game.map[i][j] = 0;
        }
    }
}

void Board::layout() {
    wall();
    paddle.draw();
    ball.draw();
    brick();
}

void Board::display() {
    gotoxy(2, 1);
    cout << "LIFE: " << Game.life;

    // 9 = side wall
    // 7 = top wall
    // 8 = score wall
    // 1 = paddle
    // 5 = ball
    // 2 = bricks
    // 0 = blanks

    for (int i = 0; i < Game.screenHeight; i++) {
        for (int j = 0; j < Game.screenWidth; j++) {
            gotoxy(j + 2, i + 3);
            if (Game.map[i][j] == 9) cout << char(219);
            if (Game.map[i][j] == 1) cout << char(219);
            if (Game.map[i][j] == 2) cout << char(233);
            if (Game.map[i][j] == 7) cout << char(219);
            if (Game.map[i][j] == 8) cout << char(240);
            if (Game.map[i][j] == 5) cout << char(254);
            if (Game.map[i][j] == 0) cout << char(32);
        }
    }
}
