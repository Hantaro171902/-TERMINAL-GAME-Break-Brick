#pragma once

#include <vector>

class BrickGrid {
public:
    int rows;
    int cols;
    int offsetX;
    int offsetY;
    std::vector<std::vector<int>> bricks; // 1 = brick, 0 = empty

    BrickGrid() : rows(7), cols(17), offsetX(6), offsetY(2) {
        bricks.assign(rows, std::vector<int>(cols, 0));
    }

    void loadHeartPattern();

    bool hitAt(int gx, int gy) {
        int bx = gx - offsetX;
        int by = gy - offsetY;
        if (bx >= 0 && bx < cols && by >= 0 && by < rows && bricks[by][bx] == 1) {
            bricks[by][bx] = 0;
            return true;
        }
        return false;
    }

    bool anyRemaining() const {
        for (const auto &row : bricks) {
            for (int v : row) if (v) return true;
        }
        return false;
    }
};


