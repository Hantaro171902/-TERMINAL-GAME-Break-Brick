#pragma once
#include <vector>

class Brick {    
public:
    static const char* skull[7];
    static const int rows = 7;
    static const int cols = 17;

    int offsetX = 6;
    int offsetY = 2;
    std::vector<std::vector<bool>> bricks; // Use bool, not Brick

    Brick();
    void loadPattern();
    void hitAt(int x, int y);
    void brick();
    // void wall();
    // void layout();
    // void display();
};