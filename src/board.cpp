#include "board.hpp"
#include <iostream>

// Define the static heart pattern
const char* Board::heart[7] = {
    "..#####...#####..",
    ".#######.#######.",
    ".###############.",
    "..#############..",
    "....#########....",
    "......#####......",
    "........#........"
};

Board::Board() {
    bricks.resize(rows, std::vector<bool>(cols, false));
    loadHeartPattern();
}

void Board::loadHeartPattern() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (heart[i][j] == '#') {
                bricks[i][j] = true;
            }
        }
    }
}

void Board::hitAt(int x, int y) {
    int gridX = x - offsetX;
    int gridY = y - offsetY;
    if (gridY >= 0 && gridY < rows && gridX >= 0 && gridX < cols) {
        bricks[gridY][gridX] = false;
    }
}

void Board::brick() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (bricks[i][j]) {
                // This will be handled by the Game class drawing
            }
        }
    }
}

void Board::wall() {
    // Wall drawing is handled by Game class
}

void Board::layout() {
    // Layout is handled by Game class
}

void Board::display() {
    // Display is handled by Game class
}
