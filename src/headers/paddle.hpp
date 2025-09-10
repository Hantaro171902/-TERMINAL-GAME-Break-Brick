#pragma once

#include "game_object.hpp"

class Paddle : public GameObject {
public:
    Paddle(int startX, int startY, int length, int thickness, const std::string& symbol);
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setVelocityY(float y);
    void setVelocityX(float x);

    void draw() const override;
    void update(float deltaTime) override;
    void setXLimits(float xMin, float xMax);

private:
    void clampToBounds() override;

private:
    float vy = 0.0f;    // vertical velocity
    float vx = 0.0f;    // horizontal velocity
    float _xMin = 0.0f;  // new horizontal min limit
    float _xMax = 0.0f;  // new horizontal max limit

};


