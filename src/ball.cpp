#include "ball.hpp"
#include "utils.hpp"
#include "color.hpp"
#include <iostream>

using namespace std;

Ball::Ball(int startX, int startY, int width, int height, const std::string& symbol)
    : GameObject(startX, startY, width, height, symbol), dx(1), dy(1), _symbol(symbol) {}

void Ball::reset(int startX, int startY) {
    _position.x = static_cast<float>(startX);
    _position.y = static_cast<float>(startY);
    dx = 1; // Reset to initial velocity
    dy = 1;
}


void Ball::updateBall(const GameObject& paddle, int screenWidth, int screenHeight) {
    // Apply deceleration to both horizontal and vertical velocities
    // if (abs(dx) > 0.01f) {
    //     dx -= signum(dx) * deceleration;
    // } else {
    //     dx = 0;
    // }

    // if (abs(dy) > 0.01f) {
    //     dy -= signum(dy) * deceleration;
    // } else {
    //     dy = 0;
    // }

    _position.x += dx;
    _position.y += dy;
    
    // Check for collision with top or bottom walls
    if (_position.y <= 1 || _position.y + getLength() >= screenHeight - 1) {
        dy = -dy;
    }
    
    // Paddle collision
    if (_position.x <= paddle.getX() + paddle.getThickness() &&
        _position.x >= paddle.getX() &&
        _position.y >= paddle.getY() &&
        _position.y < paddle.getY() + paddle.getLength()) {

        dx = -dx;
        _position.x = paddle.getX() + paddle.getThickness();

         // Add bounce physics
        // float relativeIntersectY = (paddle.getY() + (paddle.getLength() / 2)) - _position.y;
        // float normalizedRelativeIntersectionY = relativeIntersectY / (paddle.getLength() / 2);
        // dy = normalizedRelativeIntersectionY * 5.0f; // Adjust bounce speed as needed
    }

    // Right wall collision
    if (_position.x + getThickness() >= screenWidth - 1) {
        dx = -dx;
        _position.x = screenWidth - 1 - getThickness();
    }

    // Left wall collision
    if (_position.x <= 1) {
        dx = -dx;
        _position.x = 1;
    }
}

void Ball::update(float deltaTime) {
    // _position.x += dx * deltaTime;
    // _position.y += dy * deltaTime;  
}

void Ball::render() const {
    setTextColor(_color);
    move_cursor(static_cast<int>(_position.x), static_cast<int>(_position.y));
    cout << _symbol;
    resetTextColor();
    // cout << 'o';
}


// void Ball::bounceX() {
//     dx *= -1;
// }

// void Ball::bounceY() {
//     dy *= -1;
// }