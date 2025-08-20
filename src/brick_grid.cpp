#include "headers/brick_grid.hpp"

void BrickGrid::loadHeartPattern() {
    static const char* heart[] = {
        "..#####...#####..",
        ".#######.#######.",
        ".###############.",
        "..#############..",
        "....#########....",
        "......#####......",
        "........#........"
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            bricks[i][j] = (heart[i][j] == '#') ? 1 : 0;
        }
    }
}


