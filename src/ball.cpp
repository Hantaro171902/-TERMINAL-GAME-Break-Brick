#include "ball.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

Ball::Ball(int startX, int startY) : GameObject(startX, startY), speed(1), dx(1), dy(-1) {}

void Ball::reset(int startX, int startY, int dirX, int dirY) {
    x = startX;
    y = startY;
    dx = dirX;
    dy = dirY;
}

void Ball::update() {
    x += dx * speed;
    y += dy * speed;
}

void Ball::draw() {
    move_cursor(x, y);
    cout << 'o';
}

void Ball::bounceX() {
    dx *= -1;
}

void Ball::bounceY() {
    dy *= -1;
}