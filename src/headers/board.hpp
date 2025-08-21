#pragma once
#include "game.hpp"
#include <vector>

class Board {
private: 
    static const char* heart[] = {
        "..#####...#####..",
        ".#######.#######.",
        ".###############.",
        "..#############..",
        "....#########....",
        "......#####......",
        "........#........"
    };

    int rows = 7;
    int cols = 15;

public:
    void brick();
    void wall();
    void heart();
    void layout();
    void display();
};


