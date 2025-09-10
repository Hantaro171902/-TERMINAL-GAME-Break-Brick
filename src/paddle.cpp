#include "paddle.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Paddle::Paddle(int startX, int startY, int gameWidth)
    : GameObject(startX, startY), gameWidth(gameWidth), width(9), speed(10) {}

void Paddle::update() {
    // The Paddle's position is updated directly by the processInput method
}

void Paddle::draw() {
    move_cursor(x, y);
    for (int i = 0; i < width; ++i) {
        cout << BLOCK_FULL;
    }
}

void Paddle::processInput(char input) {
    // If you want to use InputKey, change the argument type to InputKey and use InputKey::LEFT, etc.
    // If you want to use char, compare to 'a'/'d' or arrow key codes as appropriate for your input system.
    if (input == 'a') {
        x = max(0, x - speed);
    } else if (input == 'd') {
        x = min(gameWidth - width, x + speed);
    }
}