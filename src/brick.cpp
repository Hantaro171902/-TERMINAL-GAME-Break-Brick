#include "brick.hpp"
#include <iostream>

// Define the static heart pattern
const char* Brick::skull[7] = {
    "...###########...",
    ".###..#####..###.",
    ".##....###....##.",
    "..##..#####..##..",
    "...####...####...",
    "......#####......",
    "......#.#.#......"
};

Brick::Brick() {
    bricks.resize(rows, std::vector<bool>(cols, false));
    loadPattern();
}

void Brick::loadPattern() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (skull[i][j] == '#') {
                bricks[i][j] = true;
            }
        }
    }
}

void Brick::hitAt(int x, int y) {
    int gridX = x - offsetX;
    int gridY = y - offsetY;
    if (gridY >= 0 && gridY < rows && gridX >= 0 && gridX < cols) {
        bricks[gridY][gridX] = false;
    }
}

void Brick::brick() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (bricks[i][j]) {
                // This will be handled by the Game class drawing
            }
        }
    }
}

