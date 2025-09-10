#pragma once

#include <iostream>
#include <string>
#include "color.hpp"
#include "utils.hpp"

struct XYPosition {
    float x;
    float y;
};

class GameObject {
public:
    int x, y;

    GameObject(int windowX, int windowY, int length, int thickness, const std::string& symbol = BLOCK_FULL);
    virtual ~GameObject() {}

    // --- geometry/state ---
    XYPosition getPosition() const;
    void setPosition(float x, float y);
    void setWindowLimits(int maxX, int maxY);

    int getLength() const;
    int getThickness() const;
    std::string getSymbol() const;
    void setSymbol(const std::string& s);

    // --- position ---
    int getX() const { return static_cast<int>(_position.x); }
    int getY() const { return static_cast<int>(_position.y); }

    // --- visuals ---
    void setColor(TextColor c);
    TextColor getColor() const;
    void switchColor();               // pick a random ANSI color

    // --- rendering ---
    virtual void draw()  const;       // prints the object
    virtual void clear() const;       // erases the object

    // --- helpers ---
    virtual void clampToBounds();             // keeps within 1..(limit-2) box

    // optional per-frame physics (no-op by default)
    virtual void update(float /*deltaTime*/) {}

protected:
    int _windowLimitX, _windowLimitY;
    XYPosition _position;
    int _length;
    int _thickness;
    std::string _symbol;
    TextColor _color = WHITE;
};  