#pragma once

#include <iostream>

class GameObject {
public:
    int x, y;

    GameObject(int startX, int startY) : x(startX), y(startY) {}

    // Pure virtual functions make this an abstract class
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~GameObject() = default;
};