#include <iostream>
#include "paddle.hpp"

using namespace std;

Paddle::Paddle() : x(0), y(0), speed(1), delay(0), count_delay(0), dir(' ') {}

void Paddle::draw() {
   for (int i = 0; i < 9; i++) {
        map[y][x + i] = 1; // Assuming map is a global or accessible variable
    }
}

void Paddle::move() {
    if (count_delay >= delay) {
        if (dir == 'L' && x - speed > 0) {
            x -= speed;
        } else if (dir == 'R' && x + speed < 80 - 9) { // Assuming screen width is 80
            x += speed;
        }
        count_delay = 0;
    }
    count_delay++;
    
    if (decre_life) {
        dir = 'S';
        x = 80 / 2 - 5; // Reset to center
        y = 30 - 30 / 7 - 1; // Reset to bottom
        decre_life = false;
    }
}
