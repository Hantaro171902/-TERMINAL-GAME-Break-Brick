#include "paddle.hpp"
#include <algorithm>

Paddle::Paddle() : x(0), y(0), speed(1), delay(1), count_delay(0), dir('S') {
}

void Paddle::reset(int startX, int startY) {
    x = startX;
    y = startY;
    dir = 'S';
    count_delay = 0;
}

void Paddle::moveLeft(int minX) {
    if (x - speed >= minX) {
        x -= speed;
    }
}

void Paddle::moveRight(int maxX) {
    if (x + speed <= maxX - 9) {  // 9 is paddle width
        x += speed;
    }
}

void Paddle::draw() {
    // Drawing is handled by Game class
}

void Paddle::move() {
    if (count_delay == delay) {
        if (dir == 'L' && x - speed > 0) {
            x -= speed;
        } else if (dir == 'R' && x + speed < 30 - 9) {  // Assuming screen width 30
            x += speed;
        }
        count_delay = 0;
    }
    count_delay++;
}
