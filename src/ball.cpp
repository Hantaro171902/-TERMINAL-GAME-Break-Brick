#include "ball.hpp"
#include <cstdlib>
#include <ctime>

Ball::Ball() : x(0), y(0), speed(1), dir(0) {
}

void Ball::reset(int startX, int startY, int dirX, int dirY) {
    x = startX;
    y = startY;
    dx = dirX;
    dy = dirY;
}

void Ball::draw() {
    // Drawing is handled by Game class
}

void Ball::move() {
    // Movement is handled by Game class with collision detection
}

bool Ball::collision(int fx, int fy) {
    // Collision detection is handled by Game class
    return false;
}

void Ball::bounce(int fx, int fy) {
    // Bounce logic is handled by Game class
}
