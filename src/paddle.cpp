#include "paddle.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

Paddle::Paddle(int startX, int startY, int length, int thickness, const std::string& symbol)
    : GameObject(startX, startY, length, thickness, symbol) {}

void Paddle::update(float deltaTime) {
    // The Paddle's position is updated directly by the processInput method

    _position.y += vy * deltaTime;
    // _position.x += vx * deltaTime;

    clampToBounds();
}

void Paddle::draw() const {
    GameObject::draw();
}


void Paddle::moveUp() {
    // auto pos = getPosition();
    // setPosition(pos.x, pos.y - 1);
    // clampToBounds();
    setVelocityY(-60.0f);
}

void Paddle::moveDown() {
    // auto pos = getPosition();
    // setPosition(pos.x, pos.y + 1);
    // clampToBounds();
    setVelocityY(60.0f);
}

void Paddle::moveLeft() {
    setVelocityX(-60.0f);
}

void Paddle::moveRight() {
    setVelocityX(60.0f);
}

void Paddle::setVelocityY(float y) {
    vy = y;
}

void Paddle::setVelocityX(float x) {
    vx = x;
}

// int Paddle::getHeight() const { return height; }
void Paddle::clampToBounds() {
    // Clamp vertical movement using the base class's logic
    int minY = 1;
    int maxY = max(1, _windowLimitY - _length - 1);
    _position.y = clamp(_position.y, static_cast<float>(minY), static_cast<float>(maxY));

    // Clamp horizontal movement using the new paddle-specific limits
    _position.x = clamp(_position.x, _xMin, _xMax);
}

void Paddle::setXLimits(float xMin, float xMax) {
    _xMin = xMin;
    _xMax = xMax;
}


// void Paddle::processInput(char input) {
//     // If you want to use InputKey, change the argument type to InputKey and use InputKey::LEFT, etc.
//     // If you want to use char, compare to 'a'/'d' or arrow key codes as appropriate for your input system.
//     if (input == 'a') {
//         x = max(0, x - speed);
//     } else if (input == 'd') {
//         x = min(gameWidth - width, x + speed);
//     }
// }